/** Interface for the root native view of a React native application */
export interface ReactRoot {

  /** This constant represents that ReactRoot hasn't started yet or it has been destroyed. */
  readonly STATE_STOPPED: number;
  
  /** This constant represents that ReactRoot has started. */
  readonly STATE_STARTED: number;
  /** Return cached launch properties for app */
  getAppProperties(): string;
  
  getJSModuleName(): string;
  
  /** Fabric or Default UI Manager, see {@link UIManagerType} */
  // getUIManagerType(): number;
  
  getRootViewTag(): number;
  
  // setRootViewTag(rootViewTag: number): void;
  
  /** Calls into JS to start the React application. */
  // runApplication(): void;
  
  /** Handler for stages {@link com.facebook.react.surface.ReactStage} */
  onStage(stage: number): void;
  
  /** Return native view for root */
  // getRootViewGroup();
  
  /** @return Cached values for widthMeasureSpec. */
  getWidthMeasureSpec(): number;
  
  /** @return Cached values for and heightMeasureSpec. */
  getHeightMeasureSpec(): number;
  
  /** Sets a flag that determines whether to log that content appeared on next view added. */
  // setShouldLogContentAppeared(shouldLogContentAppeared: boolean): void;
  
  /**
   * @return a {@link String} that represents the root js application that is being rendered with
   *     this {@link ReactRoot}
   * @deprecated We recommend to not use this method as it is will be replaced in the near future.
   */
  // getSurfaceID(): string;
  
  /** @return an {@link AtomicInteger} that represents the state of the ReactRoot object. */
  getState(): number;
}