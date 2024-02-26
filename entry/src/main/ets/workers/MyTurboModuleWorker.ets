import worker, { ThreadWorkerGlobalScope, MessageEvents, ErrorEvent } from '@ohos.worker';
import { CatalystInstanceWorkerHost } from '@ohos/react-openharmony';
import hilog from '@ohos.hilog';

const workerPort: ThreadWorkerGlobalScope = worker.workerPort;
const ReactTurboModule: CatalystInstanceWorkerHost = new CatalystInstanceWorkerHost(workerPort);

/**
 * Defines the event handler to be called when the worker thread receives a message sent by the host thread.
 * The event handler is executed in the worker thread.
 *
 * @param e message data
 */
 workerPort.onmessage = (e: MessageEvents) => {
    hilog.info(0X0000, "ReactWorker", 'receive a message "%{public}s"', e.data);
    ReactTurboModule.onmessage(e);
 }

 /**
  * Defines the event handler to be called when the worker  receives a message that cannot be deserialized.
  * The event handler is executed in the worker thread.
  *
  * @param e message data
  */

  workerPort.onmessageerror = ( e: MessageEvents) => {
    ReactTurboModule.onmessageerror(e);
  }

  /**
   * Defines the event handler to be called when an exception occurs during worker execution.
   * The event handler is executed in the worker thread.
   *
   * @param e error message
   */
   workerPort.onerror = (e: ErrorEvent) => {
    ReactTurboModule.onerror(e);
   }
 