import { JSIModuleProvider } from './JSIModuleProvider';
import { JSIModule } from './JSIModule';
import { JSIModuleType } from './JSIModuleType';

/** Holder class used to register {@link JSIModule} into JSI Bridge. */
export interface JSIModuleSpec<T extends JSIModule> {

  getJSIModuleType(): JSIModuleType;

  getJSIModuleProvider(): JSIModuleProvider<T>;
}
