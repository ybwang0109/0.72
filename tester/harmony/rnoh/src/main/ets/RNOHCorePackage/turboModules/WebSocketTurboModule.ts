import webSocket from '@ohos.net.webSocket'
import util from '@ohos.util'
import { TurboModule } from "../../RNOH/TurboModule";

const WEB_SOCKET_SUPPORTED_EVENT_NAMES = ["websocketOpen", "websocketClosed", "websocketFailed", "websocketMessage"] as const;

export class WebSocketTurboModule extends TurboModule {
  public static readonly NAME = 'WebSocketModule';

  private socketsById: Map<number, webSocket.WebSocket> = new Map();
  private base64 = new util.Base64Helper()

  getSupportedEvents() {
    return WEB_SOCKET_SUPPORTED_EVENT_NAMES
  }

  connect(url: string, protocols: string[] | undefined | null, options: { headers?: object }, socketID: number) {
    const ws = webSocket.createWebSocket();

    ws.on('open', (data) => {
      this.ctx.rnInstanceManager.emitDeviceEvent("websocketOpen", {
        id: socketID,
        protocol: "",
      });
    });

    ws.on('error', (err) => this.handleError(socketID, err));
    ws.on('message', (err, data) => {
      if (typeof data === "string") {
        this.ctx.rnInstanceManager.emitDeviceEvent("websocketMessage", {
          id: socketID,
          type: "text",
          data: data,
        });
      } else if (data instanceof ArrayBuffer) {
        const base64Data = this.base64.encodeToStringSync(new Uint8Array(data));

        this.ctx.rnInstanceManager.emitDeviceEvent("websocketMessage", {
          id: socketID,
          type: "binary",
          data: base64Data,
        });
      }
    });

    ws.on('close', (err, data) => {
      this.ctx.rnInstanceManager.emitDeviceEvent("websocketClosed", {
        id: socketID,
        ...data,
      })
    })

    ws.connect(url, { header: options.headers }, (err) => this.handleError(socketID, err));
    this.socketsById.set(socketID, ws);
  }

  send(message: string, socketID: number) {
    const ws = this.socketsById.get(socketID);
    if (!ws) {
      throw new Error(`Trying to send a message on websocket "${socketID}" but there is no socket.`);
    }

    ws.send(message, (err) => this.handleError(socketID, err));
  }

  sendBinary(base64Message: string, socketID: number) {
    const ws = this.socketsById.get(socketID);
    if (!ws) {
      throw new Error(`Trying to send a message on websocket "${socketID}" but there is no socket.`);
    }

    const message = this.base64.decodeSync(base64Message);
    ws.send(message.buffer, (err) => this.handleError(socketID, err));
  }

  ping(socketID: number) {
    const ws = this.socketsById.get(socketID);
    if (!ws) {
      throw new Error(`Trying to send a ping on websocket "${socketID}" but there is no socket.`);
    }

    this.ctx.logger.warn("WebSocketTurboModule::ping not implemented");
  }

  close(code: number, reason: string, socketID: number) {
    const ws = this.socketsById.get(socketID);
    if (!ws) {
      throw new Error(`Trying to close websocket "${socketID}" but there is no socket.`);
    }

    ws.close({ code, reason }, (err) => this.handleError(socketID, err));
    this.socketsById.delete(socketID);
  }

  private handleError(socketID: number, err) {
    if (err) {
      this.ctx.logger.info(`WebSocketTurboModule::handleError ${JSON.stringify(err)}`);
      this.ctx.rnInstanceManager.emitDeviceEvent("websocketFailed", { id: socketID, message: JSON.stringify(err) });
      this.socketsById.delete(socketID);
    }
  }
}
