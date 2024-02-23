import { CatalystInstanceWorkerClient } from './CatalystInstanceWorkerClient'
import { CatalystInstance } from './interface/CatalystInstance'
import worker from '@ohos.worker';
import { CatalystInstanceImpl } from './CatalystInstanceImpl';

export class CatalystInstanceBuilder {

  private mTruboModuleWorkerInstance: worker.ThreadWorker | null = null;
  // private JSBundleLoader mJSBundleLoader;
  // private NativeModuleRegistry mRegistry;
  // private JavaScriptExecutor mJSExecutor;
  // private JSExceptionHandler mJSExceptionHandler;

  public setReactQueueConfigurationSpec(TruboModuleWorkerInstance : worker.ThreadWorker | null): CatalystInstanceBuilder {
	this.mTruboModuleWorkerInstance = TruboModuleWorkerInstance;
  return this;
}
//
// public Builder setRegistry(NativeModuleRegistry registry) {
//   mRegistry = registry;
//   return this;
// }
//
// public Builder setJSBundleLoader(JSBundleLoader jsBundleLoader) {
//   mJSBundleLoader = jsBundleLoader;
//   return this;
// }
//
// public Builder setJSExecutor(JavaScriptExecutor jsExecutor) {
//   mJSExecutor = jsExecutor;
//   return this;
// }
//
// public Builder setJSExceptionHandler(JSExceptionHandler handler) {
//   mJSExceptionHandler = handler;
//   return this;
// }

  public build(): CatalystInstance {
	if ( this.mTruboModuleWorkerInstance != null ){
	  //todo: 应该从Host开始获取实例名称
	  return new CatalystInstanceWorkerClient("testInstance",this.mTruboModuleWorkerInstance)
	} else {
	  // let mtaskThread: TaskExecutor | null = new TaskExecutor();
	  // TaskExecutor.initMainTaskRunnerFromUiThread();
	  return new CatalystInstanceImpl("testInstance")
	}

  // return new CatalystInstanceImpl(
  //   Assertions.assertNotNull(mReactQueueConfigurationSpec),
  //   Assertions.assertNotNull(mJSExecutor),
  //   Assertions.assertNotNull(mRegistry),
  //   Assertions.assertNotNull(mJSBundleLoader),
  //   Assertions.assertNotNull(mJSExceptionHandler));
}
}