import { TurboModuleManagerDelegate } from '../turbo_module/interface/TurboModuleManagerDelegate';
import type { TurboModule, TurboModuleContext } from '../turbo_module/TurboModule';
import {
	DeviceInfoTurboModule,
	SafeAreaTurboModule,
} from './turboModules';

const TURBO_MODULE_CLASS_BY_NAME = [
  DeviceInfoTurboModule.NAME,
  SafeAreaTurboModule.NAME
]

export class CoreTurboModulesFactory extends TurboModuleManagerDelegate {

	createTurboModule(name: string): TurboModule | null {
    if (this.hasTurboModule(name)) {
      // return new TURBO_MODULE_CLASS_BY_NAME[name](this.ctx);
      if (name == DeviceInfoTurboModule.NAME) {
        return new DeviceInfoTurboModule(this.ctx)
      }
      if (name == SafeAreaTurboModule.NAME) {
        return new SafeAreaTurboModule(this.ctx)
      }
    }
    return null;
  }

  hasTurboModule(name: string): boolean {
    for (let i of TURBO_MODULE_CLASS_BY_NAME) {
      if (i == name) {
        return true;
      }
    }
    return false;
  }
}
