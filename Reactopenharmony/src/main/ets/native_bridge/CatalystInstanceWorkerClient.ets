import { CatalystInstance } from './interface/CatalystInstance';
import worker, { ThreadWorkerGlobalScope, MessageEvents, ErrorEvent } from '@ohos.worker';
import hilog from '@ohos.hilog';
import { JSIModule } from '../JSIModule/JSIModule';
import { JSIModuleType } from '../JSIModule/JSIModuleType';
import { JSIModuleSpec } from '../JSIModule/JSIModuleSpec';
import ArrayList from '@ohos.util.ArrayList';
import { JSIModuleRegistry } from '../JSIModule/JSIModuleRegistry';


export class CatalystInstanceWorkerClient implements CatalystInstance {
  private mTruboModuleWorkerInstance: worker.ThreadWorker;
  private mInstanceName: string
  private mJSIModuleRegistry: JSIModuleRegistry = new JSIModuleRegistry();

  constructor(instanceName: string, TruboModuleWorkerInstance: worker.ThreadWorker) {
    this.mTruboModuleWorkerInstance = TruboModuleWorkerInstance;
    this.mInstanceName = instanceName;

    // todo:需要传递的参数有JsExecutorFactory、JsBundleLoader、Packages和JSIModulePackage
    this.mTruboModuleWorkerInstance.postMessage("Create_CatalystInstance");

    this.mTruboModuleWorkerInstance.onmessage = (e: MessageEvents) => {
      // 接收Worker发送的消息并处理
      if (e.data == "initMainTaskRunnerFromUiThread") {
        hilog.info(0x0000, "reactOpenHarmony", '%{public}s', 'CatalystInstanceWorkerHost initMainTaskRunnerFromUiThread');
        // TaskExecutor.initMainTaskRunnerFromUiThread();
      }
    }

    // todo:这里应该使用一个异步方法，等待CatalystInstance初始化完成。
  }

  addJSIModules(jsiModules: ArrayList<JSIModuleSpec<JSIModule>>): void {
    this.mJSIModuleRegistry.registerModules(jsiModules);
  }

  getJSIModule(moduleType: JSIModuleType): JSIModule {
    return this.mJSIModuleRegistry.getModule(moduleType);
  }


  runJSBundle(): void {
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }

  initialize(): void {
    throw new Error('Method not implemented.');
  }

  destroy(): void {
    throw new Error('Method not implemented.');
  }

  isDestroyed(): boolean {
    throw new Error('Method not implemented.');
  }
}