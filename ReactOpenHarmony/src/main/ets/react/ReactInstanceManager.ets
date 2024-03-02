import hilog from '@ohos.hilog';
import worker from '@ohos.worker';
import { JSIModulePackage } from '../JSIModule/JSIModulePackage';
import { ReactInstanceManagerBuilder } from './ReactInstanceManagerBuilder';
import { ReactRoot } from "./ReactRoot"
import { ReactApplicationContext } from "./ReactApplicationContext"
import { CatalystInstance } from '../native_bridge/interface/CatalystInstance';
import { JavaScriptExecutorFactory } from '../native_bridge/interface/JavaScriptExecutorFactory'
import { JSBundleLoader } from '../native_bridge/interface/JSBundleLoader'
import ReactContext from './ReactContext'
import { CatalystInstanceBuilder } from '../native_bridge/CatalystInstanceBuilder';
import { JSIModuleType } from '../JSIModule/JSIModuleType';
import ArrayList from '@ohos.util.ArrayList';
import { UIManager } from '../fabric/interface/UIManager';
import { CoreTurboModulesFactory } from "../react_core_package/Package";
import {TurboModuleManager} from '../turbo_module/TurboModuleManager'
import { TurboModuleManagerDelegate } from '../turbo_module/interface/TurboModuleManagerDelegate';

export class ReactInstanceManager {
  private readonly ReactInstanceManager = "ReactInstanceManager"
  private mApplicationContext: Context;
  private mTruboModuleWorkerInstance: worker.ThreadWorker | null;
  private mJSIModulePackage: JSIModulePackage;
  // // Identifies whether the instance manager is or soon will be initialized (on background thread)
  private mHasStartedCreatingInitialContext: boolean = false;
  private mHasStartedDestroying: boolean = false;
  private mJavaScriptExecutorFactory: JavaScriptExecutorFactory | null = null;
  private mBundleLoader: JSBundleLoader | null = null;
  private mCurrentReactContext: ReactContext | null = null;
  private mAttachedReactRoots: ArrayList<ReactRoot> = new ArrayList<ReactRoot>();

  /** Creates a builder that is capable of creating an instance of {@link ReactInstanceManager}. */
  public static builder(): ReactInstanceManagerBuilder {
    return new ReactInstanceManagerBuilder();
  }

  public constructor(
    applicationContext: Context,
    WorkerInstance: worker.ThreadWorker | null,
    jsiModulePackage: JSIModulePackage
  ) {
    hilog.info(0x0000, this.ReactInstanceManager, '%{public}s', 'ReactInstanceManager constructor');

    this.mApplicationContext = applicationContext; //实际上当前给定的是AbilityStageContext
    this.mTruboModuleWorkerInstance = WorkerInstance;
    this.mJSIModulePackage = jsiModulePackage;
    // // this.mTMMDelegateBuilder = tmmDelegateBuilder;
    // this.mPackages = new ArrayList<ReactPackage>();
    // this.mPackages.add(
    //   new CoreModulesPackage(this,new DefaultHardwareBackBtnHandlerImpl(this)));
    return;
  }

  /**
   * Trigger react context initialization asynchronously in a background async task. This enables
   * applications to pre-load the application JS, and execute global code before {@link
   * ReactRootView} is available and measured.
   *
   * <p>Called from UI thread.
   */
  public createReactContextInBackground(): void {
    hilog.info(0x0000, this.ReactInstanceManager, '%{public}s', 'createReactContextInBackground');
    //如果已经创建了,就不用重复创建了
    if (!this.mHasStartedCreatingInitialContext) {
      this.mHasStartedCreatingInitialContext = true;
      this.recreateReactContextInBackgroundInner();
    }
  }

  /**
   * @return whether createReactContextInBackground has been called. Will return false after
   *     onDestroy until a new initial context has been created.
   */
  public hasStartedCreatingInitialContext(): boolean {
    return this.mHasStartedCreatingInitialContext;
  }

  private recreateReactContextInBackgroundInner() {
    // todo: 如果是调试模式，在启动调试后异步执行实例创建
    // if (mUseDeveloperSupport && mJSMainModulePath != null){
    //   this.recreateReactContextInBackgroundFromBundleLoader();
    //   return;
    // }
    this.recreateReactContextInBackgroundFromBundleLoader();
  }

  private recreateReactContextInBackgroundFromBundleLoader() {
    this.recreateReactContextInBackground
    (this.mJavaScriptExecutorFactory as JavaScriptExecutorFactory,
      this.mBundleLoader as JSBundleLoader);
  }

  private recreateReactContextInBackground(
    jsExecutorFactory: JavaScriptExecutorFactory, jsBundleLoader: JSBundleLoader): void {

    const initParams: ReactContextInitParams =
      new ReactContextInitParams(jsExecutorFactory, jsBundleLoader);

    this.runCreateReactContextOnNewThread(initParams);

  }

  private runCreateReactContextOnNewThread(initParams: ReactContextInitParams) {

    if (this.mCurrentReactContext != null) {
      this.tearDownReactContext(this.mCurrentReactContext);
      this.mCurrentReactContext = null;
    }
    //以下逻辑Android在一个独立线程中完成,但是OpenHarmony无法通过线程完成.可以考虑下面流程使用异步方法.
    {
      while (this.mHasStartedDestroying) {
        //todo: 等待销毁的动作完成,可以使用Atomics.wait();
      }

      this.mHasStartedCreatingInitialContext = true;

      const reactApplicationContext: ReactApplicationContext =
        this.createReactContext(// initParams.getJsExecutorFactory().create(),
          initParams.getJsBundleLoader());
      //UIManager和TMM安装完成，并且RN instance完成了Bundle加载，则认为是实例创建完成了

      //Android是在NativeModule线程执行如下操作
      this.setupReactContext(reactApplicationContext);
    }
  }


  private createReactContext(
    // jsExecutor: JavaScriptExecutor,
    jsBundleLoader: JSBundleLoader): ReactApplicationContext {

    const reactContext: ReactApplicationContext = new ReactApplicationContext(this.mApplicationContext);

    const catalystInstanceBuilder: CatalystInstanceBuilder =
      new CatalystInstanceBuilder()
        .setReactQueueConfigurationSpec(this.mTruboModuleWorkerInstance)

    const catalystInstance: CatalystInstance = catalystInstanceBuilder.build();

    reactContext.initializeWithInstance(catalystInstance);

    if (this.mJSIModulePackage != null) {
      catalystInstance.addJSIModules(
        this.mJSIModulePackage.getJSIModules(reactContext));

      //todo:需要改造成getJSIModule方式
      const turboModuleFactory: TurboModuleManagerDelegate = new CoreTurboModulesFactory(reactContext);

      new TurboModuleManager(turboModuleFactory);

      catalystInstance.getJSIModule(JSIModuleType.UIManager);
    }

    //PRE_RUN_JS_BUNDLE_START
    // ReactMarker.logMarker(ReactMarkerConstants.PRE_RUN_JS_BUNDLE_START);
    // Systrace.beginSection(TRACE_TAG_REACT_JAVA_BRIDGE, "runJSBundle");
    catalystInstance.runJSBundle();
    // Systrace.endSection(TRACE_TAG_REACT_JAVA_BRIDGE);

    return reactContext;
  }

  private async setupReactContext(reactContext: ReactApplicationContext) {
    { //在这个过程中,完成attachRootViewToInstance
      this.mCurrentReactContext = reactContext;
      let catalystInstance: CatalystInstance = reactContext.getCatalystInstance();
      catalystInstance.initialize();
      //mMemoryPressureRouter.addMemoryPressureListener(catalystInstance); todo: 待增加对MemoryLevel的监听
    }
    for (const reactRoot of this.mAttachedReactRoots) {
      if (reactRoot.getState() == reactRoot.STATE_STOPPED) {
        this.attachRootViewToInstance(reactRoot);
      }
    }
  }

  private tearDownReactContext(reactContext: ReactContext): void {
    //todo:待补充实例销毁的流程
  }

  /**
   * Attach given {@param reactRoot} to a catalyst instance manager and start JS application using
   * JS module provided by {@link ReactRootView#getJSModuleName}. If the react context is currently
   * being (re)-created, or if react context has not been created yet, the JS application associated
   * with the provided reactRoot reactRoot will be started asynchronously, i.e this method won't
   * block. This reactRoot will then be tracked by this manager and in case of catalyst instance
   * restart it will be re-attached.
   */
  public attachRootView(reactRoot: ReactRoot): void {
    // Calling clearReactRoot is necessary to initialize the Id on reactRoot
    // This is necessary independently if the RN Bridge has been initialized or not.
    // Ideally reactRoot should be initialized with id == NO_ID
    if (this.mAttachedReactRoots.add(reactRoot)) {
      this.clearReactRoot(reactRoot);
    }

    // If react context is being created in the background, JS application will be started
    // automatically when creation completes, as reactRoot reactRoot is part of the attached
    // reactRoot reactRoot list.
    let currentContext: ReactContext = this.mCurrentReactContext as ReactContext;
    if (currentContext != null) {
      if (reactRoot.getState() == reactRoot.STATE_STOPPED) {
        this.attachRootViewToInstance(reactRoot);
      }
    }
  }

  private attachRootViewToInstance(reactRoot: ReactRoot): void {
    // throw new Error('Method not implemented.');

    let a: ReactContext = this.mCurrentReactContext as ReactContext;
    let b: CatalystInstance = a.getCatalystInstance();
    let uiManager: UIManager = b.getJSIModule(JSIModuleType.UIManager) as UIManager;

    let rootTag: number = uiManager.startSurface(
      reactRoot,
      reactRoot.getJSModuleName(),
      reactRoot.getAppProperties(),
      reactRoot.getWidthMeasureSpec(),
      reactRoot.getHeightMeasureSpec());

    reactRoot.onStage(101);
  }

  clearReactRoot(reactRoot: ReactRoot) {
    // 初始化RootView
  }
}

class ReactContextInitParams {
  private mJsExecutorFactory: JavaScriptExecutorFactory;
  private mJsBundleLoader: JSBundleLoader;

  constructor(
    jsExecutorFactory: JavaScriptExecutorFactory, jsBundleLoader: JSBundleLoader) {
    this.mJsExecutorFactory = jsExecutorFactory;
    this.mJsBundleLoader = jsBundleLoader;
  }

  public getJsExecutorFactory(): JavaScriptExecutorFactory {
    return this.mJsExecutorFactory;
  }

  public getJsBundleLoader(): JSBundleLoader {
    return this.mJsBundleLoader;
  }
}