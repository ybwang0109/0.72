export class TaskExecutor{
  constructor();
  static initMainTaskRunnerFromUiThread(): void;
}

export class NativeCatalystInstance{
  constructor();

  initializeBridge( a: TaskExecutor ): void;
}

export const add: (a: number, b: number) => number;