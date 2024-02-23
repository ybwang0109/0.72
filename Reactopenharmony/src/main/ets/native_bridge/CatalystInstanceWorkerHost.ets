import worker, { ThreadWorkerGlobalScope, MessageEvents, ErrorEvent } from '@ohos.worker';
import hilog from '@ohos.hilog';
import { CatalystInstanceImpl } from './CatalystInstanceImpl';

// todo：需要给
export class CatalystInstanceWorkerHost{
  private  mWorkerPort: ThreadWorkerGlobalScope

  constructor(workerPort: ThreadWorkerGlobalScope) {
	this.mWorkerPort = workerPort;
  }

  public onmessage(e: MessageEvents){

	//todo: 需要给每一个ReactInstanceManager创建一个实例，所以需要有实例标识，先不区分是哪个实例
	if(e.data == "Create_CatalystInstance"){
	  hilog.info(0x0000, "ReactWorker", '%{public}s', 'Create_CatalystInstance');

	  //先创建TaskRunner，然后再传给CatalystInstanceImpl，创建TaskRunner，需要出发initMainTaskRunner
	  // let mtaskThread: TaskExecutor | null = new TaskExecutor();
	  // this.mWorkerPort.postMessage("initMainTaskRunnerFromUiThread")
	  const instanceName: string = "testInstance";

	  new CatalystInstanceImpl(instanceName)

	} else if (e.data == "Post_CatalystInstance"){
	  hilog.info(0x0000, "ReactWorker", '%{public}s', 'Post_CatalystInstance');
	}else{
	  hilog.info(0x0000, "ReactWorker", '%{public}s', 'unkonw Message');
	}
  }

  public onmessageerror(e: MessageEvents){

  }

  public onerror(e: ErrorEvent){

  }
}