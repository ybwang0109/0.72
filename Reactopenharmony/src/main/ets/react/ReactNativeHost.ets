import hilog from '@ohos.hilog';
import worker from '@ohos.worker';
import { ReactInstanceManager } from './ReactInstanceManager';
import { ReactInstanceManagerBuilder } from './ReactInstanceManagerBuilder';

export abstract class ReactNativeHost {
  private mApplicationContext: Context;
  private mReactInstanceManager: ReactInstanceManager | null = null;
  private static instance: ReactNativeHost;
  private readonly ReactNativeHost = "ReactNativeHost"

  public constructor(applicationContext:Context) {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'ReactNativeHost constructor');
	this.mApplicationContext = applicationContext;
	ReactNativeHost.instance = this;
  }

  public static getInstance(): ReactNativeHost | null {
	if (!ReactNativeHost.instance) {
	  return null;
	}
	return ReactNativeHost.instance;
  }

  /** Get the current {@link ReactInstanceManager} instance, or create one. */
  public  getReactInstanceManager():ReactInstanceManager {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'getReactInstanceManager');
	if (this.mReactInstanceManager == null) {
	  //ReactMarker.logMarker(ReactMarkerConstants.GET_REACT_INSTANCE_MANAGER_START);
	  this.mReactInstanceManager = this.createReactInstanceManager();
	  //ReactMarker.logMarker(ReactMarkerConstants.GET_REACT_INSTANCE_MANAGER_END);
	}
	return this.mReactInstanceManager as ReactInstanceManager;
  }

  protected  createReactInstanceManager(): ReactInstanceManager {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'createReactInstanceManager');

	//ReactMarker.logMarker(ReactMarkerConstants.BUILD_REACT_INSTANCE_MANAGER_START);
	let builder: ReactInstanceManagerBuilder =
	ReactInstanceManager.builder()
	  .setApplication(this.mApplicationContext)
		// .setJSMainModulePath(this.getJSMainModuleName())
		// .setUseDeveloperSupport(this.getUseDeveloperSupport())
		// .setDevSupportManagerFactory(this.getDevSupportManagerFactory())
		// .setRequireActivity(getShouldRequireActivity())
		// .setSurfaceDelegateFactory(getSurfaceDelegateFactory())
		// .setLazyViewManagersEnabled(getLazyViewManagersEnabled())
		// .setRedBoxHandler(getRedBoxHandler())
		// .setJavaScriptExecutorFactory(getJavaScriptExecutorFactory())
	  .setJSIModulesPackage(this.getJSIModulePackage())
		// .setInitialLifecycleState(LifecycleState.BEFORE_CREATE)
		// .setReactPackageTurboModuleManagerDelegateBuilder(
		//   this.getReactPackageTurboModuleManagerDelegateBuilder());
	  .setTurboModuleWorker(this.getTurboModuleWorker())
	;

	// for (ReactPackage reactPackage : getPackages()) {
	//   builder.addPackage(reactPackage);
	// }
	//
	// let  jsBundleFile: String = this.getJSBundleFile();
	// if (jsBundleFile != null) {
	//   builder.setJSBundleFile(jsBundleFile);
	// } else {
	//   builder.setBundleAssetName(this.getBundleAssetName());
	// }
	let reactInstanceManager: ReactInstanceManager = builder.build();
	// ReactMarker.logMarker(ReactMarkerConstants.BUILD_REACT_INSTANCE_MANAGER_END);
	return reactInstanceManager;
  }

  /**
   * Returns the name of the main module. Determines the URL used to fetch the JS bundle from Metro.
   * It is only used when dev support is enabled. This is the first file to be executed once the
   * {@link ReactInstanceManager} is created. e.g. "index.android"
   */
  protected  getJSMainModuleName():string {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'getJSMainModuleName');
	return "index";
  }

  /** Returns whether dev mode should be enabled. This enables e.g. the dev menu. */
  public abstract  getUseDeveloperSupport():boolean

  /**
   * Returns a custom path of the bundle file. This is used in cases the bundle should be loaded
   * from a custom path. By default it is loaded from Android assets, from a path specified by
   * {@link getBundleAssetName}. e.g. "file://sdcard/myapp_cache/index.android.bundle"
   */
  protected  getJSBundleFile():string | null {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'getJSBundleFile');
	return null;
  }

  /**
   * Returns the name of the bundle in assets. If this is null, and no file path is specified for
   * the bundle, the app will only work with {@code getUseDeveloperSupport} enabled and will always
   * try to load the JS bundle from Metro. e.g. "index.android.bundle"
   */
  protected  getBundleAssetName(): String {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'getBundleAssetName');
	return "index.android.bundle";
  }

  /**
   * Get whether this holder contains a {@link ReactInstanceManager} instance, or not. I.e. if
   * {@link #getReactInstanceManager()} has been called at least once since this object was created
   * or {@link #clear()} was called.
   */
  public  hasInstance(): boolean {
	hilog.info(0x0000, this.ReactNativeHost, '%{public}s', 'hasInstance');
	return this.mReactInstanceManager != null;
  }

  protected abstract getJSIModulePackage()

  public abstract  getTurboModuleWorker(): worker.ThreadWorker | null
}