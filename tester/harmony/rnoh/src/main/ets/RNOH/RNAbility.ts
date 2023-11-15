import UIAbility from '@ohos.app.ability.UIAbility';
import { NapiBridge } from "./NapiBridge"
import type { RNOHLogger } from "./RNOHLogger";
import { StandardRNOHLogger } from "./RNOHLogger"
import type window from '@ohos.window';
import hilog from '@ohos.hilog';
import type { TurboModuleProvider } from "./TurboModuleProvider"
import libRNOHApp from 'librnoh_app.so'
import { RNInstanceRegistry } from './RNInstanceRegistry';
import type { RNInstance, RNInstanceOptions } from './RNInstance';
import { RNOHContext } from "./RNOHContext"

export abstract class RNAbility extends UIAbility {
  protected storage: LocalStorage
  protected napiBridge: NapiBridge = null
  protected turboModuleProvider: TurboModuleProvider
  protected logger: RNOHLogger
  protected rnInstanceRegistry: RNInstanceRegistry
  protected window: window.Window | undefined

  async onCreate(want, param) {
    this.logger = this.createLogger()
    this.napiBridge = new NapiBridge(libRNOHApp)
    this.rnInstanceRegistry = new RNInstanceRegistry(
      this.logger,
      this.napiBridge,
      this.context,
      (rnInstance) => this.createRNOHContext({
        rnInstance
      }))
    AppStorage.setOrCreate('RNOHLogger', this.logger)
    AppStorage.setOrCreate('RNInstanceFactory', this.rnInstanceRegistry)
    AppStorage.setOrCreate('RNAbility', this)
  }

  public async createAndRegisterRNInstance(options: RNInstanceOptions): Promise<RNInstance> {
    return await this.rnInstanceRegistry.createInstance(options)
  }

  public destroyAndUnregisterRNInstance(rnInstance: RNInstance): void {
    this.rnInstanceRegistry.deleteInstance(rnInstance.getId())
  }

  public createRNOHContext({rnInstance}: Pick<RNOHContext, "rnInstance">) {
    return new RNOHContext("0.0.0", rnInstance, this.logger)
  }

  protected createLogger(): RNOHLogger {
    return new StandardRNOHLogger();
  }

  public getLogger(): RNOHLogger {
    return this.logger
  }

  public async onWindowSetup(win: window.Window) {
    await win.setWindowLayoutFullScreen(true)
  }

  onWindowStageCreate(windowStage: window.WindowStage) {
    this.onWindowSetup(windowStage.getMainWindowSync()).then(() => {
      windowStage.loadContent(this.getPagePath(), (err, data) => {
        if (err.code) {
          hilog.error(0x0000, 'RNOH', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err) ?? '');
          return;
        }
        hilog.info(0x0000, 'RNOH', 'Succeeded in loading the content. Data: %{public}s', JSON.stringify(data) ?? '');
      });
    }).catch((reason) => {
      hilog.error(0x0000, 'RNOH', 'Failed to setup window. Cause: %{public}s', JSON.stringify(reason) ?? '');
    })
  }

  onMemoryLevel(level) {
    const MEMORY_LEVEL_NAMES = ["MEMORY_LEVEL_MODERATE", "MEMORY_LEVEL_LOW", "MEMORY_LEVEL_CRITICAL"]
    this.logger.debug("Received memory level event: " + MEMORY_LEVEL_NAMES[level])
    this.napiBridge.onMemoryLevel(level)
  }

  onConfigurationUpdate(config) {
    this.rnInstanceRegistry.forEach((rnInstance) => rnInstance.onConfigurationUpdate(config))
  }

  onForeground() {
    this.rnInstanceRegistry.forEach((rnInstance) => rnInstance.onForeground())
  }

  onBackground() {
    this.rnInstanceRegistry.forEach((rnInstance) => rnInstance.onBackground())
  }

  onBackPress() {
    this.rnInstanceRegistry.forEach((rnInstance) => rnInstance.onBackPress())
    return true;
  }

  abstract getPagePath(): string
}
