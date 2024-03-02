import { JSIModule } from './JSIModule';

export interface JSIModuleProvider<T extends JSIModule> {
  get(): T;
}
