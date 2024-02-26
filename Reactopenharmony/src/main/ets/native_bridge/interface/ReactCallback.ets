//todo: 实现CallBack相关能力，保证同一时刻，只能有一个JSCall
export interface ReactCallback {
  onBatchComplete(): void;  //会调用到UIManagerModule的onBatchComplete()方法；
  incrementPendingJSCalls(): void;
  decrementPendingJSCalls(): void;
}