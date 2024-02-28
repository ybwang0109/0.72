import { TurboModule, TurboModuleContext } from "../../turbo_module/TurboModule";

interface SafeAreaInsets {
  top: number,
  left: number,
  right: number,
  bottom: number
}

const defaultDisplayMetrics: SafeAreaInsets = {
  top: 38.857142857142854,
  left: 8,
  right: 8,
  bottom: 0
};

export class SafeAreaTurboModule extends TurboModule {
  public static readonly NAME = 'SafeAreaTurboModule';

  public getInitialInsets(): SafeAreaInsets {

    return defaultDisplayMetrics
  }
}


