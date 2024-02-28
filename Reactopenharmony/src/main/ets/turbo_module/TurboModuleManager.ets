import hilog from '@ohos.hilog';
import { turbo_module_manager } from 'libreact_arkui.so'
import { JSIModule } from '../JSIModule/JSIModule';
import type { TurboModule, TurboModuleContext } from "../turbo_module/TurboModule";
import { TurboModuleManagerDelegate } from './interface/TurboModuleManagerDelegate';

export class TurboModuleManager implements JSIModule {
  private readonly TurboModuleManager = "TurboModuleManager"
  private nativeTurboModuleManager: turbo_module_manager;
  // private turboModulesFactories: TurboModulesFactory[];
  private static turboModuleProvider: TurboModuleProvider | null = null; //todo:临时先放到这里，不然TurboModuleProvider被销毁TurboModule就不能用了

  constructor(turboModuleFactory: TurboModuleManagerDelegate) {
    hilog.info(0x0000, this.TurboModuleManager, 'TurboModuleManager constructor begin');

    TurboModuleManager.turboModuleProvider = new TurboModuleProvider([turboModuleFactory]);

    this.nativeTurboModuleManager = new turbo_module_manager(this, TurboModuleManager.turboModuleProvider);
    this.nativeTurboModuleManager.installJSIBindings();

    hilog.info(0x0000, this.TurboModuleManager, 'TurboModuleManager constructor end');
  }

  initialize(): void {
    throw new Error('Method not implemented.');
  }

  onCatalystInstanceDestroy(): void {
    throw new Error('Method not implemented.');
  }

  getModule(name: string) {
    hilog.info(0x0000, this.TurboModuleManager, 'TurboModuleManager getModule %{public}s', name);
  }
}

class TurboModuleProvider {
  private cachedTurboModuleByName: Record<string, TurboModule | null> = {};
  private turboModulesFactories: TurboModuleManagerDelegate[];

  constructor(turboModulesFactories: TurboModuleManagerDelegate[]) {
    this.turboModulesFactories = turboModulesFactories;
  }

  getModule<T extends TurboModule>(name: string): T {
    for (let i of Object.keys(this.cachedTurboModuleByName)) {
      if (i == name) {
        return this.cachedTurboModuleByName[name] as T;
      }
    }

    for (const tmFactory of this.turboModulesFactories) {
      if (tmFactory.hasTurboModule(name)) {
        this.cachedTurboModuleByName[name] = tmFactory.createTurboModule(name);
        if (this.cachedTurboModuleByName[name] === null) {
          throw new Error(`Couldn't create "${name}" Turbo Module`);
        }
      }
    }
    return this.cachedTurboModuleByName[name] as T;
  }

  hasModule(name: string) {
    for (const tmFactory of this.turboModulesFactories) {
      if (tmFactory.hasTurboModule(name)) {
        return true;
      }
    }
    return false;
  }
}