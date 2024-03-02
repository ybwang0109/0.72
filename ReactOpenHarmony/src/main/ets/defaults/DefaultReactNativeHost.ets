import worker from '@ohos.worker';
import { ReactNativeHost } from '../react/ReactNativeHost';
import { JSIModulePackage } from '../JSIModule/JSIModulePackage';

import { DefaultJSIModulePackage } from './DefaultJSIModulePackage';

export class DefaultReactNativeHost extends ReactNativeHost {
  TAG = "DefaultReactNativeHost"

  public getUseDeveloperSupport(): boolean {
    throw new Error('Method not implemented.');
  }

  public getTurboModuleWorker(): worker.ThreadWorker | null {
    return null;
  }

  protected getJSIModulePackage(): JSIModulePackage | null {
    if (this.isNewArchEnabled()) {
      return new DefaultJSIModulePackage(this);
    } else {
      return null
    }
  }

  protected isNewArchEnabled(): boolean {
    return true;
  }

  protected isHermesEnabled(): boolean {
    return true;
  }
}