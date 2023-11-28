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
        major: this.ctx.reactNativeVersion.split('.', 3)[0],
        minor: this.ctx.reactNativeVersion.split('.', 3)[1],
        patch: this.ctx.reactNativeVersion.split('.', 3)[2],
      }
    };
  }
}