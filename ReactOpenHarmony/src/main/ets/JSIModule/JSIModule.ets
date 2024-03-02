/** Marker interface used to represent a JSI Module. */
export interface JSIModule {

  /**
   * This is called at the end of {@link CatalystApplicationFragment#createCatalystInstance()} after
   * the CatalystInstance has been created, in order to initialize NativeModules that require the
   * CatalystInstance or JS modules.
   */
  initialize(): void;

  /** Called before {CatalystInstance#onHostDestroy} */
  onCatalystInstanceDestroy(): void;
}