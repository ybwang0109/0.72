import ArrayList from '@ohos.util.ArrayList';
import { CatalystInstance } from './interface/CatalystInstance';
import { JSIModuleType } from '../JSIModule/JSIModuleType';
import { JSIModuleSpec } from '../JSIModule/JSIModuleSpec';
import { JSIModule } from '../JSIModule/JSIModule';
import { JSIModuleRegistry } from '../JSIModule/JSIModuleRegistry';
import hilog from '@ohos.hilog';
import {native_catalyst_instance} from 'libreact_arkui.so'
import { JSBundleLoader } from './interface/JSBundleLoader';

class PendingJSCall {
  public mModule: string;
  public mMethod: string;
  public mArguments: string;

  public constructor(module: string, method: string, argument: string) {
	this.mModule = module;
	this.mMethod = method;
	this.mArguments = argument;
  }

  call(catalystInstance: CatalystInstanceImpl): void {
	// catalystInstance.jniCallJSFunction(mModule, mMethod, arguments);
  }
}

export class CatalystInstanceImpl implements CatalystInstance {

  private mDestroyed: boolean = false;
  private mAcceptCalls: boolean = false;
  private mJSCallsPendingInit: ArrayList<PendingJSCall> = new ArrayList<PendingJSCall>();
  private mJSBundleLoader: JSBundleLoader | null = null;
  private mJSBundleHasLoaded: boolean = false;
  private mNativeCatalystInstance: native_catalyst_instance;

  constructor( instanceName: string ) {

	hilog.info(0x0000, 'reactOpenHarmony', 'CatalystInstanceImpl constructor');

	this.mNativeCatalystInstance = new native_catalyst_instance(instanceName);

	this.mNativeCatalystInstance.initializeBridge();
  }

  runJSBundle(): void {
	this.mNativeCatalystInstance.loadScriptFromFile("fileName","sourceURL",true);
	// this.mJSBundleLoader.loadScript(CatalystInstanceImpl.this);  todo: 补充使用JSBundleLoader加载Bundle的流程
	// synchronized (mJSCallsPendingInitLock) {

	// Loading the bundle is queued on the JS thread, but may not have
	// run yet.  It's safe to set this here, though, since any work it
	// gates will be queued on the JS thread behind the load.
	this.mAcceptCalls = true;

	this.mJSCallsPendingInit.forEach((func) => {
	  func.call(this);
	})
	this.mJSCallsPendingInit.clear();

	// }
	this.mJSBundleHasLoaded = true;
  }

  hasRunJSBundle(): boolean {
	throw new Error('Method not implemented.');
  }

  getSourceURL(): string {
	throw new Error('Method not implemented.');
  }

  invokeCallback(callbackID: number, argument: string): void {
	throw new Error('Method not implemented.');
  }

  callFunction(module: string, method: string, argument: String): void {
	// this.callFunctioninner(new PendingJSCall(module, method, argument));
  }

  callFunctionInner(func: PendingJSCall) {
	if (this.mDestroyed) {
	  // final String call = function.toString();
	  // FLog.w(ReactConstants.TAG, "Calling JS function after bridge has been destroyed: " + call);
	  return;
	}
	if (!this.mAcceptCalls) {
	  this.mJSCallsPendingInit.add(func);
	  return;
	}
	func.call(this);
  }

  destroy(): void {
	throw new Error('Method not implemented.');
  }

  initialize(): void {
	// throw new Error('Method not implemented.');
  }

  isDestroyed(): boolean {
	throw new Error('Method not implemented.');
  }

  private mJSIModuleRegistry: JSIModuleRegistry = new JSIModuleRegistry();

  addJSIModules(jsiModules: ArrayList<JSIModuleSpec<JSIModule>> ): void {
	this.mJSIModuleRegistry.registerModules(jsiModules);
  }

  getJSIModule(moduleType: JSIModuleType): JSIModule {
	return this.mJSIModuleRegistry.getModule(moduleType);
  }
}