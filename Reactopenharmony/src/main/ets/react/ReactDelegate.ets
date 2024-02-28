import hilog from '@ohos.hilog';
import UIAbility from '@ohos.app.ability.UIAbility';
import { ReactInstanceManager } from "./ReactInstanceManager"
import { ReactNativeHost } from './ReactNativeHost';
import { ReactRootView } from './ReactRootView';

export class ReactDelegate {
  private readonly ReactDelegate: string = "ReactDelegate"
  private mAbility: UIAbility;
  private mReactNativeHost: ReactNativeHost;
  private mMainComponentName: string;
  private mLaunchOptions: string;
  private mReactRootView: ReactRootView | null = null;

  public constructor(
    Ability: UIAbility,
    ReactNativeHost: ReactNativeHost,
    MainComponentName: string,
    LaunchOptions: string) {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'constructor');
    this.mAbility = Ability;
    this.mReactNativeHost = ReactNativeHost;
    this.mMainComponentName = MainComponentName;
    this.mLaunchOptions = LaunchOptions;
  }

  public loadApp(appKey: string): void {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'loadApp');
    if (this.mReactRootView != null) {
      throw new Error("Cannot loadApp while app is already running.");
    }

    //todo: 应该写成可重载方法，但是没有调通，后续修改
    if (appKey == null) {
      appKey = this.mMainComponentName;
    }

    //todo:未来ArkUI提供C++ API的时候，可以换掉这个地方，创建一个不同的RootView
    this.mReactRootView = this.createRootView();
    this.mReactRootView.startReactApplication(
      this.getReactNativeHost().getReactInstanceManager(), appKey, this.mLaunchOptions);
  }


  //在声明式UI环境下，ReactRootView等同于ViewModule，用于跟RNSurfaceView绑定使用。
  public getReactRootView(): ReactRootView {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'getReactRootView');
    return this.mReactRootView as ReactRootView;
  }

  protected createRootView(): ReactRootView {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'createRootView');
    return new ReactRootView(this.mAbility);
  }

  /** Get the {@link ReactNativeHost} used by this app. */
  private getReactNativeHost(): ReactNativeHost {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'getReactNativeHost');
    return this.mReactNativeHost;
  }

  private getReactInstanceManager(): ReactInstanceManager {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'getReactInstanceManager');
    return this.mReactNativeHost.getReactInstanceManager();
  }

  public onHostResume() {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'onHostResume');
    // this.getReactInstanceManager()?.onHostResume(this.mAbility,null);
  }

  public onHostPause() {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'onHostPause');
    // this.getReactInstanceManager()?.onHostPause(this.mAbility);
  }

  public onHostDestroy() {
    hilog.info(0x0000, this.ReactDelegate, '%{public}s', 'onHostDestroy');
    // if (this.mReactRootView != null) {
    //   this.mReactRootView.unmountReactApplication();
    //   this.mReactRootView = null;
    // }
    if (this.mReactNativeHost.hasInstance()) {
      // this.getReactInstanceManager().onHostDestroy(this.mAbility);
    }
  }
}
