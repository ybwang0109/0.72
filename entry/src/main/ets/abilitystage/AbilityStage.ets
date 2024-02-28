import AbilityStage from '@ohos.app.ability.AbilityStage';
import worker from '@ohos.worker';
import hilog from '@ohos.hilog';
import { ReactApplication, ReactNativeHost, DefaultReactNativeHost } from '@ohos/react-openharmony';

class MyReactNativeHost extends DefaultReactNativeHost {
  readonly TAG = "testTag ReactNativeHost"

  public constructor(applicationContext: Context) {
    super(applicationContext);
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost constructor');
  }

  public getJSMainModuleName(): string {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost getJSMainModuleName');
    return "index";
  }

  public getBundleAssetName(): string {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost getBundleAssetName');
    return "RNTesterApp.android.bundle";
  }

  public getUseDeveloperSupport(): boolean {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost getUseDeveloperSupport');
    return false;
  }

  public getPackages(): void {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost getPackages');
    return;
  }

  public getTurboModuleWorker(): worker.ThreadWorker | null {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost getArkTSWorker');
    const workerInstance: worker.ThreadWorker = new worker.ThreadWorker('entry/ets/workers/MyTurboModuleWorker.ets');
    workerInstance.postMessage("hello worker");
    // return workerInstance;
    return null;
  }

  protected isNewArchEnabled(): boolean {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost isNewArchEnabled');
    return true;
  }

  protected isHermesEnabled(): boolean {
    hilog.info(0x0000, this.TAG, '%{public}s', 'MyReactNativeHost isHermesEnabled');
    return true;
  }
}

export default class RNTAbilityStage extends AbilityStage implements ReactApplication {
  private readonly TAG = "testTag RNTAbilityStage"
  private myReactNativeHost: ReactNativeHost | null = null;

  onCreate() {
    hilog.info(0x0000, this.TAG, '%{public}s', 'RNTAbilityStage onCreate');
    // 在应用的AbilityStage onCreate 生命周期启动初始化ReactNativeHost并创建ReactInstanceManager实例
    this.myReactNativeHost = new MyReactNativeHost(this.context.getApplicationContext()) as ReactNativeHost;
    //todo:ReactInstanceManager实例创建可以是异步的？
    this.myReactNativeHost.getReactInstanceManager()

  }

  //todo:待OS能力补齐后取消全局变量的获取方式
  getReactNativeHost(): ReactNativeHost | null {
    hilog.info(0x0000, this.TAG, '%{public}s', 'RNTAbilityStage getReactNativeHost');
    return this.myReactNativeHost;
  }
}