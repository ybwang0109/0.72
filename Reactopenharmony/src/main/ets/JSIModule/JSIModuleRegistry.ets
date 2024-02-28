import ArrayList from '@ohos.util.ArrayList';
import HashMap from '@ohos.util.HashMap';
import { JSIModule } from './JSIModule';
import { JSIModuleSpec } from './JSIModuleSpec';
import { JSIModuleHolder } from './JSIModuleHolder';
import { JSIModuleType } from './JSIModuleType';

export class JSIModuleRegistry {
  private mModules: HashMap<JSIModuleType, JSIModuleHolder> = new HashMap<JSIModuleType, JSIModuleHolder>();

  constructor() {
  }

  getModule(moduleType: JSIModuleType) {
    let jsiModuleHolder = this.mModules.get(moduleType);
    if (jsiModuleHolder == null) {
      throw new Error("Unable to find JSIModule for class " + moduleType);
    }
    let jsiModule: JSIModule = jsiModuleHolder.getJSIModule();
    if (jsiModule == null) {
      throw new Error("Unable to find JSIModule for class " + moduleType + " in JSIModuleHolder");
    }
    return jsiModule;
  }

  registerModules(jsiModules: ArrayList<JSIModuleSpec<JSIModule>>) {
    for (let spec of jsiModules) {
      this.mModules.set(spec.getJSIModuleType(), new JSIModuleHolder(spec));
    }
  }

  notifyJSInstanceDestroy() {
    for (let moduleType of this.mModules.keys()) {
      if (moduleType == JSIModuleType.TurboModuleManager) {
        continue;
      }

      let moduleHolder: JSIModuleHolder = this.mModules.get(moduleType);
      moduleHolder.notifyJSInstanceDestroy();
    }
  }
}
