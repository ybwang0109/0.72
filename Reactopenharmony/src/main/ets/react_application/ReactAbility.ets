import hilog from '@ohos.hilog';
import window from '@ohos.window';
import Want from '@ohos.app.ability.Want';
import UIAbility from '@ohos.app.ability.UIAbility';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import { ReactAbilityDelegate } from './ReactAbilityDelegate';
import { ReactRootView } from '../react/ReactRootView';

/** Base Activity for React Native applications. */
/** 抽象类，用于绑定ReactAbility的生命周期 */
export abstract class ReactAbility extends UIAbility{
  private ReactAbility = "ReactAbility"

  private mDelegate: ReactAbilityDelegate;
  private mReactRootView: ReactRootView | undefined = undefined;

  protected constructor() {
    super();
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'constructor');
    this.mDelegate = this.createReactActivityDelegate();
  }

  /**
   * Returns the name of the main component registered from JavaScript. This is used to schedule
   * rendering of the component. e.g. "MoviesApp"
   */
  protected abstract getMainComponentName():string;

  protected abstract getLocalStorage():LocalStorage;

  /** Called at construction time, override if you have a custom delegate implementation. */
  protected  createReactActivityDelegate():ReactAbilityDelegate {
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'createReactActivityDelegate');
    return new ReactAbilityDelegate(this, this.getMainComponentName());
  }

  public setContentView(contentView: ReactRootView | undefined): void {
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'setContentView');
    this.mReactRootView = contentView;
  }

  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam) {
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'onCreate');
    super.onCreate(want, launchParam);
    this.mDelegate.onCreate();

    let storage = this.getLocalStorage();
    storage.setOrCreate('ReactViewModule', this.mReactRootView )
  }

  onDestroy() {
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'onDestroy');
    super.onDestroy();
    this.mDelegate.onDestroy();
  }

  onWindowStageDestroy() {
    // Main window is destroyed, release UI related resources
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'onWindowStageDestroy');
  }

  onForeground() {
    // Ability has brought to foreground
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'onForeground');
    super.onForeground();
    this.mDelegate.onForeground();
  }

  onBackground() {
    // Ability has back to background
    hilog.info(0x0000, this.ReactAbility, '%{public}s', 'onBackground');
    super.onBackground();
    this.mDelegate.onBackground();
  }

}