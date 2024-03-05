import { ReactApplicationContext } from "../react/ReactApplicationContext"

/** All turbo modules should inherit from this interface */
export class TurboModule {
  /** Initialize the TurboModule. */
  // initialize(): void;

  /** Called before React Native is torn down. Clean up after the TurboModule. */
  // invalidate(): void;

  public static readonly NAME: string;
  protected ctx: TurboModuleContext

  public constructor(context: TurboModuleContext) {
    this.ctx = context;
  }
}

export type TurboModuleContext = ReactApplicationContext;