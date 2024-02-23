import worker from '@ohos.worker';
import { JSIModulePackage } from '../JSIModule/JSIModulePackage';
import { ReactInstanceManager } from './ReactInstanceManager';


export class ReactInstanceManagerBuilder {

  private mApplicationContext: Context| undefined = undefined;
  private mJSMainModulePath: string = "";
  private mUseDeveloperSupport: boolean = false;
  private mJSBundleAssetUrl: string | null = null;
  private mJSIModulesPackage: JSIModulePackage | undefined = undefined;
  private mTruboModuleWorkerInstance: worker.ThreadWorker | null = null;

  // private mTMMDelegateBuilder: ReactPackageTurboModuleManagerDelegateBuilder;
  // private mJSBundleLoader: JSBundleLoader;

  public setTurboModuleWorker(workerInstance: worker.ThreadWorker | null ){
	this.mTruboModuleWorkerInstance = workerInstance;
	return this;
  }

  public setJSIModulesPackage(jsiModulePackage: JSIModulePackage): ReactInstanceManagerBuilder {
	this.mJSIModulesPackage = jsiModulePackage;
	return this;
  }

  /** Required. This must be your {@code Application} instance. */
  public setApplication(applicationContext: Context):ReactInstanceManagerBuilder {
	this.mApplicationContext = applicationContext;
	return this;
  }

  /**
   * Path to your app's main module on Metro. This is used when reloading JS during development. All
   * paths are relative to the root folder the packager is serving files from. Examples: {@code
   * "index.android"} or {@code "subdirectory/index.android"}
   */
  public setJSMainModulePath( jsMainModulePath: string): ReactInstanceManagerBuilder {
	this.mJSMainModulePath = jsMainModulePath;
	return this;
  }

  /**
   * When {@code true}, developer options such as JS reloading and debugging are enabled. Note you
   * still have to call {@link #showDevOptionsDialog} to show the dev menu, e.g. when the device
   * Menu button is pressed.
   */
  public  setUseDeveloperSupport( useDeveloperSupport: boolean): ReactInstanceManagerBuilder {
	this.mUseDeveloperSupport = useDeveloperSupport;
	return this;
  }

  /**
   * Path to the JS bundle file to be loaded from the file system.
   *
   * <p>Example: {@code "assets://index.android.js" or "/sdcard/main.jsbundle"}
   */
  public  setJSBundleFile( jsBundleFile: string): ReactInstanceManagerBuilder {
	if (jsBundleFile.startsWith("assets://")) {
	  this.mJSBundleAssetUrl = jsBundleFile;
	  // this.mJSBundleLoader = null;
	  return this;
	}
	//todo:需要适配JSBundleLoader能力
	// return this.setJSBundleLoader(JSBundleLoader.createFileLoader(jsBundleFile));
	return this;
  }

  /**
   * Bundle loader to use when setting up JS environment. This supersedes prior invocations of
   * {@link setJSBundleFile} and {@link setBundleAssetName}.
   *
   * <p>Example: {@code JSBundleLoader.createFileLoader(application, bundleFile)}
   */
  //todo:需要适配JSBundleLoader能力
  // public  setJSBundleLoader( jsBundleLoader: JSBundleLoader): ReactInstanceManagerBuilder {
  //   this.mJSBundleLoader = jsBundleLoader;
  //   this.mJSBundleAssetUrl = null;
  //   return this;
  // }

  /**
   * Name of the JS bundle file to be loaded from application's raw assets. Example: {@code
   * "index.android.js"}
   */
  public  setBundleAssetName( bundleAssetName: string):ReactInstanceManagerBuilder {
	this.mJSBundleAssetUrl = (bundleAssetName == null ? null : "assets://" + bundleAssetName);
	//todo:需要适配JSBundleLoader能力
	// this.mJSBundleLoader = null;
	return this;
  }

  // public setReactPackageTurboModuleManagerDelegateBuilder(builder: ReactPackageTurboModuleManagerDelegateBuilder): ReactInstanceManagerBuilder {
  //   this.mTMMDelegateBuilder = builder;
  // return this;
  // }

  /**
   * Instantiates a new {@link ReactInstanceManager}. Before calling {@code build}, the following
   * must be called:
   *
   * <ul>
   *   <li>{@link #setApplication}
   *   <li>{@link #setCurrentActivity} if the activity has already resumed
   *   <li>{@link #setDefaultHardwareBackBtnHandler} if the activity has already resumed
   *   <li>{@link #setJSBundleFile} or {@link #setJSMainModulePath}
   * </ul>
   */
  public  build(): ReactInstanceManager {
	return new ReactInstanceManager(
	  this.mApplicationContext as Context,
	  this.mTruboModuleWorkerInstance,
	  this.mJSIModulesPackage as JSIModulePackage,
	);
  }
}