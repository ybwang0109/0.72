import { TurboModule, TurboModuleContext } from "../../turbo_module/TurboModule";

interface PhysicalPixels {
  width: number,
  height: number,
  scale: number,
  fontScale: number,
  densityDpi: number,
}

interface DisplayMetrics {
  windowPhysicalPixels: PhysicalPixels,
  screenPhysicalPixels: PhysicalPixels,
};

interface ret {
  Dimensions: DisplayMetrics;
}

const defaultDisplayMetrics: ret = {
  Dimensions: {
    windowPhysicalPixels: {
      width: 1344,
      height: 2772,
      scale: 3.5,
      fontScale: 1,
      densityDpi: 560,
    },
    screenPhysicalPixels: {
      width: 1344,
      height: 2772,
      scale: 3.5,
      fontScale: 1,
      densityDpi: 560
    }
  }
};

export class DeviceInfoTurboModule extends TurboModule {
  public static readonly NAME = 'DeviceInfo';

  getConstants() {
    return defaultDisplayMetrics;
  };
}
