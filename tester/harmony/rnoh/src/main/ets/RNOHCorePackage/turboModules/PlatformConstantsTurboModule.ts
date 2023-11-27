import deviceInfo from "@ohos.deviceInfo";
import { TurboModule } from "../../RNOH/TurboModule";

export class PlatformConstantsTurboModule extends TurboModule {
  public static readonly NAME = 'PlatformConstants';

  getConstants() {
    return {
      Model: deviceInfo.productModel,
      deviceType: deviceInfo.deviceType,
      osFullName: deviceInfo.osFullName,
      isTesting: false,
      reactNativeVersion: {
        major: 0,
        minor: 72,
        patch: 5,
      }
    };
  }
}