import ArrayList from '@ohos.util.ArrayList';
import { TurboModule } from '../TurboModule'

/** Interface to allow for creating and retrieving TurboModules. */
export interface TurboModuleRegistry {

  /**
   * Return the TurboModule instance that has that name `moduleName`. If the `moduleName`
   * TurboModule hasn't been instantiated, instantiate it. If no TurboModule is registered under
   * `moduleName`, return null.
   */
  getModule(moduleName: string): TurboModule;

  /** Get all instantiated TurboModules. */
  getModules(): ArrayList<TurboModule>;

  /** Has the TurboModule with name `moduleName` been instantiated? */
  hasModule(moduleName: string): boolean;

  /**
   * Return the names of all the NativeModules that are supposed to be eagerly initialized. By
   * calling getModule on each name, this allows the application to eagerly initialize its
   * NativeModules.
   */
  getEagerInitModuleNames(): ArrayList<String>;
}