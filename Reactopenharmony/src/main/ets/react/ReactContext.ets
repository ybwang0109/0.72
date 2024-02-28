import UIAbility from '@ohos.app.ability.UIAbility';
import hilog from '@ohos.hilog';
import { CatalystInstance } from '../native_bridge/interface/CatalystInstance';

// import { CatalystInstance } from './interfaces/CatalystInstance';

// todo: 研究一下ReactContext是否需要继承OpenHarmonyAppContext？Android有个ContextWrapper能力
export default class ReactContext {
  private readonly tagReactContext: string = "ReactContext"
  private context: Context
  private mCatalystInstance: CatalystInstance | null = null;
  private mDestroyed: boolean = false;

  //todo:在ReactContext中创建RCTDeviceEventEmitter，用于向RN JS发送事件

  public constructor(context: Context) {
    this.context = context;
    hilog.info(0x0000, this.tagReactContext, '%{public}s', 'constructor');
  }

  /** Set and initialize CatalystInstance for this Context. This should be called exactly once. */
  public initializeWithInstance(catalystInstance: CatalystInstance): void {

    if (catalystInstance == null) {
      throw new Error('CatalystInstance cannot be null.');
    }

    if (this.mCatalystInstance != null) {
      throw new Error('ReactContext has been already initialized');
    }

    if (this.mDestroyed) {
      throw new Error('Cannot initialize ReactContext after it has been destroyed.');
      // ReactSoftExceptionLogger.logSoftException(
      //   TAG,
      //   new IllegalStateException("Cannot initialize ReactContext after it has been destroyed."));
    }

    this.mCatalystInstance = catalystInstance;

    // 在OpenHarmony场景下，不需要在这里初始化线程
    // ReactQueueConfiguration queueConfig = catalystInstance.getReactQueueConfiguration();
    // initializeMessageQueueThreads(queueConfig);

    // todo:待实现JavaScriptModule能力
    // initializeInteropModules();
  }

  public getCatalystInstance(): CatalystInstance {
    return this.mCatalystInstance as CatalystInstance;
  }

  public onHostResume(activity: UIAbility): void {
    hilog.info(0x0000, this.tagReactContext, '%{public}s', 'onHostResume');
  }

  /** Should be called by the hosting Fragment in {@link Fragment#onPause} */
  public onHostPause(): void {
    hilog.info(0x0000, this.tagReactContext, '%{public}s', 'onHostPause');
  }

  /** Should be called by the hosting Fragment in {@link Fragment#onDestroy} */
  public onHostDestroy(): void {
    hilog.info(0x0000, this.tagReactContext, '%{public}s', 'onHostDestroy');
  }

  /** @return true if there is an non-null, alive react native instance */
  // public hasActiveReactInstance(): boolean {
  //   return this.mCatalystInstance != null && !this.mCatalystInstance.isDestroyed();
  // }
  //
  // public getCatalystInstance(): CatalystInstance {
  //   return this.mCatalystInstance;
  // }
}