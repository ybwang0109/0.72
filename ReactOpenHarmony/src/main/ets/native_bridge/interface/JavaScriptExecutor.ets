export interface JavaScriptExecutor {

  /**
   * Close this executor and cleanup any resources that it was using. No further calls are expected
   * after this. TODO mhorowitz: This may no longer be used; check and delete if possible.
   */
  close(): void

  /** Returns the name of the executor, identifying the underlying runtime. */
  getName(): string;
}