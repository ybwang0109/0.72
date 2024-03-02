import ArrayList from '@ohos.util.ArrayList';
import { ReactApplicationContext } from '../react/ReactApplicationContext';
import { JSIModule } from './JSIModule';
import { JSIModuleSpec }from './JSIModuleSpec';

/** Interface used to initialize JSI Modules into the JSI Bridge. */
export interface JSIModulePackage {

  /** @return a {@link List< JSIModuleSpec >} that contain the list of JSI Modules. */
  getJSIModules(reactApplicationContext: ReactApplicationContext): ArrayList<JSIModuleSpec<JSIModule>>;

  getImportPath(): string;
}
