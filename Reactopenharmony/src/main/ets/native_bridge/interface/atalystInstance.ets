/**
 * A higher level API on top of the asynchronous JSC bridge. This provides an environment allowing
 * the invocation of JavaScript methods and lets a set of Java APIs be invokable from JavaScript as
 * well.
 */
 import { JSIModule } from '../../JSIModule/JSIModule';
 import { JSIModuleSpec } from '../../JSIModule/JSIModuleSpec';
 import { JSIModuleType } from '../../JSIModule/JSIModuleType';
 import ArrayList from '@ohos.util.ArrayList';
 
 /**
  * A higher level API on top of the asynchronous JSC bridge. This provides an environment allowing
  * the invocation of JavaScript methods and lets a set of Java APIs be invocable from JavaScript as
  * well.
  */
 export interface CatalystInstance {
 
   runJSBundle(): void;
 
   // Returns the status of running the JS bundle; waits for an answer if runJSBundle is running
   hasRunJSBundle(): boolean;
 
   /**
	* Return the source URL of the JS Bundle that was run, or {@code null} if no JS bundle has been
	* run yet.
	*/
   getSourceURL(): string;
 
   // This is called from java code, so it won't be stripped anyway, but proguard will rename it,
   // which this prevents.
   invokeCallback(callbackID: number, argument: string): void;
 
   callFunction(module: string, method: string, argument: String): void;
 
   /**
	* Destroys this catalyst instance, waiting for any other threads in ReactQueueConfiguration
	* (besides the UI thread) to finish running. Must be called from the UI thread so that we can
	* fully shut down other threads.
	*/
   destroy(): void;
 
   isDestroyed(): boolean;
 
   /** Initialize all the native modules */
   initialize(): void;
 
   // <T extends JavaScriptModule> T getJSModule(Class<T> jsInterface);
 
   // <T extends NativeModule> boolean hasNativeModule(Class<T> nativeModuleInterface);
 
   // <T extends NativeModule> T getNativeModule(Class<T> nativeModuleInterface);
   //
   // NativeModule getNativeModule(String moduleName);
 
   getJSIModule(moduleType: JSIModuleType): JSIModule;
 
   // Collection<NativeModule> getNativeModules();
 
   /**
	* This method permits a CatalystInstance to extend the known Native modules. This provided
	* registry contains only the new modules to load.
	*/
   // void extendNativeModules(NativeModuleRegistry modules);
 
   /**
	* Adds a idle listener for this Catalyst instance. The listener will receive notifications
	* whenever the bridge transitions from idle to busy and vice-versa, where the busy state is
	* defined as there being some non-zero number of calls to JS that haven't resolved via a
	* onBatchCompleted call. The listener should be purely passive and not affect application logic.
	*/
   // void addBridgeIdleDebugListener(NotThreadSafeBridgeIdleDebugListener listener);
 
   /**
	* Removes a NotThreadSafeBridgeIdleDebugListener previously added with {@link
	* #addBridgeIdleDebugListener}
	*/
   // void removeBridgeIdleDebugListener(NotThreadSafeBridgeIdleDebugListener listener);
 
   /** This method registers the file path of an additional JS segment by its ID. */
   // void registerSegment(int segmentId, String path);
   // void setGlobalVariable(String propName, String jsonValue);
 
   // RuntimeExecutor getRuntimeExecutor();
   //
   // RuntimeScheduler getRuntimeScheduler();
 
   addJSIModules(jsiModules: ArrayList<JSIModuleSpec<JSIModule>>): void;
 
   /**
	* Returns a hybrid object that contains a pointer to a JS CallInvoker, which is used to schedule
	* work on the JS Thread. Required for TurboModuleManager initialization.
	*/
   // CallInvokerHolder getJSCallInvokerHolder();
 
   /**
	* Returns a hybrid object that contains a pointer to a Native CallInvoker, which is used to
	* schedule work on the NativeModules thread. Required for TurboModuleManager initialization.
	*/
   // CallInvokerHolder getNativeCallInvokerHolder();
 
   /**
	* For the time being, we want code relying on the old infra to also work with TurboModules.
	* Hence, we must provide the TurboModuleRegistry to CatalystInstance so that getNativeModule,
	* hasNativeModule, and getNativeModules can also return TurboModules.
	*/
   // void setTurboModuleManager(JSIModule getter);
 }