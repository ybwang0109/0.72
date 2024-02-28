import hilog from '@ohos.hilog';
import { ReactNativeHost } from '../react/ReactNativeHost';
import { ReactDelegate } from "../react/ReactDelegate"
import { ReactAbility } from './ReactAbility';

/**
 * Delegate class for {@link ReactActivity}. You can subclass this to provide custom implementations
 * for e.g. {@link #getReactNativeHost()}, if your Application class doesn't implement {@link
 * ReactApplication}.
 */
export class ReactAbilityDelegate {
  // private static readonly mConcurrentRootEnabled: boolean = false
  private readonly ReactAbilityDelegate = "ReactAbilityDelegate"
  private mReactDelegate: ReactDelegate | null = null;
  private mAbility: ReactAbility;
  private mMainComponentName: string;

  public constructor(Ability: ReactAbility, MainComponentName: string) {
    this.mAbility = Ability;
    this.mMainComponentName = MainComponentName;
  }

  public getMainComponentName(): string {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'getMainComponentName');
    return this.mMainComponentName;
  }

  /**
   * Public API to populate the launch options that will be passed to React. Here you can customize
   * the values that will be passed as `initialProperties` to the Renderer.
   *
   * @return Either null or a key-value map as a Bundle
   */
  protected getLaunchOptions(): string | null {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'getLaunchOptions');
    return null;
  }

  /**
   * Override this method to enable Concurrent Root on the surface for this Activity. See:
   * https://reactjs.org/blog/2022/03/29/react-v18.html
   *
   * <p>This requires to be rendering on Fabric (i.e. on the New Architecture).
   *
   * @return Wether you want to enable Concurrent Root for this surface or not.
   */
  protected isConcurrentRootEnabled(): boolean {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'isConcurrentRootEnabled');
    return false;
  }

  protected getPlainAbility(): ReactAbility {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'getPlainActivity');
    return this.mAbility;
  }

  private composeLaunchOptions(): string {
    let composedLaunchOptions: string | null = this.getLaunchOptions();
    if (this.isConcurrentRootEnabled()) {
      if (composedLaunchOptions == null) {
        composedLaunchOptions = "";
      }
      //composedLaunchOptions.putBoolean("concurrentRoot", true);
    }
    return composedLaunchOptions as string;
  }

  /**
   * Get the {@link ReactNativeHost} used by this app. By default, assumes {@link
   * Activity#getApplication()} is an instance of {@link ReactApplication} and calls {@link
   * ReactApplication#getReactNativeHost()}. Override this method if your application class does not
   * implement {@code ReactApplication} or you simply have a different mechanism for storing a
   * {@code ReactNativeHost}, e.g. as a static field somewhere.
   */
  protected getReactNativeHost(): ReactNativeHost {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'getReactNativeHost');
    return ReactNativeHost.getInstance() as ReactNativeHost;
  }

  public onCreate() {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'onCreate');
    let mainComponentName: string = this.getMainComponentName();
    let launchOptions: string = this.composeLaunchOptions();
    this.mReactDelegate =
      new ReactDelegate(
        this.getPlainAbility(), this.getReactNativeHost(), mainComponentName, launchOptions);

    if (mainComponentName != null) {
      this.loadApp(mainComponentName);
    }
  }

  protected loadApp(appKey: string): void {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'loadApp');
    this.mReactDelegate?.loadApp(appKey);
    this.getPlainAbility().setContentView(this.mReactDelegate?.getReactRootView());
  }

  public onDestroy() {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'onDestroy');
    // this.mReactDelegate?.onHostDestroy();
  }


  public onForeground() {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'onForeground');
    // this.mReactDelegate?.onHostResume();
  }

  public onBackground() {
    hilog.info(0x0000, this.ReactAbilityDelegate, '%{public}s', 'onBackground');
    // this.mReactDelegate?.onHostPause();
  }
}