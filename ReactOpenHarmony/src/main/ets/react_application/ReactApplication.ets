import { ReactNativeHost } from '../react/ReactNativeHost';

export interface ReactApplication {
  /** Get the default {@link ReactNativeHost} for this app. */
   getReactNativeHost(): ReactNativeHost | null
}