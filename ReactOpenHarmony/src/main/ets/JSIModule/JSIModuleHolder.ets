import { JSIModuleSpec } from './JSIModuleSpec';
import { JSIModule } from './JSIModule';

export class JSIModuleHolder {
  private mModule: JSIModule | null = null;
  private mSpec: JSIModuleSpec<JSIModule>;

  constructor(spec: JSIModuleSpec<JSIModule>) {
    this.mSpec = spec;
  }

  public getJSIModule() {
    if (this.mModule == null) {
      this.mModule = this.mSpec.getJSIModuleProvider().get();
      this.mModule.initialize();
    }
    return this.mModule;
  }

  public notifyJSInstanceDestroy() {
    if (this.mModule != null) {
      this.mModule.onCatalystInstanceDestroy();
    }
  }
}