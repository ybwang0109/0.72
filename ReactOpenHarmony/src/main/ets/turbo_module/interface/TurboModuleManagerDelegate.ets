import type { TurboModule, TurboModuleContext } from "../TurboModule";

export abstract class TurboModuleManagerDelegate {
  protected ctx: TurboModuleContext;
  public constructor(context: TurboModuleContext) {
    this.ctx = context;
  }

  abstract createTurboModule(name: string): TurboModule | null;

  abstract hasTurboModule(name: string): boolean;
}