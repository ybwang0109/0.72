import {JavaScriptExecutor} from './JavaScriptExecutor'


export interface JavaScriptExecutorFactory {
  create(): JavaScriptExecutor;

  /**
   * Starts the sampling profiler for this specific JavaScriptExecutor Sampling profiler is usually
   * a singleton on the runtime, hence the method exists here and not in {@link JavaScriptExecutor}
   */
  //todo: startSamplingProfiler(): void;

  /**
   * Stops the Sampling profile
   *
   * @param filename The filename where the results of the sampling profiler are dumped to
   */
  //todo: stopSamplingProfiler(filename: string): void;
}