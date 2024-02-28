import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import hilog from '@ohos.hilog';
import UIAbility from '@ohos.app.ability.UIAbility';
import Want from '@ohos.app.ability.Want';
import window from '@ohos.window';

import { ReactAbility,ReactAbilityDelegate,DefaultReactAbilityDelegate } from '@ohos/react-openharmony';

class RNTesterAbilityDelegate extends DefaultReactAbilityDelegate {
  private readonly TAG1 = "testTag AbilityDelegate"
  private mInitialProps: string = "";

  public constructor(Ability: ReactAbility, MainComponentName: string) {
    super(Ability, MainComponentName)
    hilog.info(0x0000, this.TAG1, '%{public}s', 'constructor');
  }

  public onCreate(): void {
    hilog.info(0x0000, this.TAG1, '%{public}s', 'onCreate');
    // Get remote param before calling super which uses it
    this.mInitialProps = "";
    super.onCreate();
  }

  protected getLaunchOptions(): string {
    hilog.info(0x0000, this.TAG1, '%{public}s', 'getLaunchOptions');
    return this.mInitialProps;
  }
}

export default class EntryAbility extends ReactAbility {
  private mlocalStorage: LocalStorage = new LocalStorage();
  private readonly EntryAbility = "testTag EntryAbility"

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(0x0000, this.EntryAbility, '%{public}s', 'Ability onWindowStageCreate');

    windowStage.loadContent('pages/Index', this.mlocalStorage, (err, data) => {
      if (err.code) {
        hilog.error(0x0000, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err) ?? '');
        return;
      }
      hilog.info(0x0000, 'testTag', 'Succeeded in loading the content. Data: %{public}s', JSON.stringify(data) ?? '');
    });
  }

  protected createReactActivityDelegate(): ReactAbilityDelegate {
    hilog.info(0x0000, this.EntryAbility, '%{public}s', 'createReactActivityDelegate');
    return new RNTesterAbilityDelegate(this, this.getMainComponentName());
  }

  protected getMainComponentName(): string {
    hilog.info(0x0000, this.EntryAbility, '%{public}s', 'getMainComponentName');
    return "RNTesterApp";
  }

  protected getLocalStorage(): LocalStorage {
    return this.mlocalStorage
  }
};
