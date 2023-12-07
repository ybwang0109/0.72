import hilog from '@ohos.hilog';

export interface RNOHLogger {
  info(...args: any[]): void

  warn(...args: any[]): void

  error(...args: any[]): void

  fatal(...args: any[]): void

  debug(...args: any[]): void

  clone(pathSegment: string | string[]): RNOHLogger

  startTracing(): () => void
}

export class Tracer {
  private activeTracesCount: number = 0

  public startTrace(name: string) {
    this.activeTracesCount++
    return () => {
      this.activeTracesCount--
    }
  }

  public getActiveTracesCount(): number {
    return this.activeTracesCount
  }
}

type Severity = "info" | "debug" | "fatal" | "error" | "warn"
type ScheduledLog = {
  args: any[],
  formattedPath: string,
  offset: number,
  severity: Severity,
  createdAt: Date,
  timer?: ReturnType<typeof setTimeout>
  logFn: (scheduledLog: Omit<ScheduledLog, "logFn">, throttlesCount: number) => void
}


export class StandardRNOHLogger implements RNOHLogger {
  private static scheduleLog(newScheduledLog: ScheduledLog) {
    const cls = StandardRNOHLogger
    if (cls.recentLog) {
      if (cls.THROTTLE_IN_MS === 0) {
        cls.scheduledLog = newScheduledLog
        cls.flushScheduledLog()
      } else if (cls.hasLogChanged(newScheduledLog)) {
        cls.flushScheduledLog()
        cls.scheduledLog = { ...newScheduledLog, timer: setTimeout(() => {
          cls.flushScheduledLog()
        }, cls.THROTTLE_IN_MS) }
      } else if ((new Date().getTime() - cls.THROTTLE_IN_MS) < (cls.scheduledLog?.createdAt?.getTime() ?? 0)) {
        cls.recentThrottlesCount++
      } else {
        cls.scheduledLog = { ...newScheduledLog, timer: setTimeout(() => {
          cls.flushScheduledLog()
        }, cls.THROTTLE_IN_MS) }
      }
    } else {
      cls.scheduledLog = newScheduledLog
      cls.flushScheduledLog()
    }
  }


  private static flushScheduledLog() {
    const cls = StandardRNOHLogger
    if (cls.scheduledLog?.timer) {
      clearTimeout(cls.scheduledLog.timer)
      cls.scheduledLog.timer = undefined
    }
    if (cls.scheduledLog) {
      cls.scheduledLog.logFn(cls.scheduledLog, cls.recentThrottlesCount)
      cls.recentThrottlesCount = 0
      cls.recentLog = cls.scheduledLog
      cls.scheduledLog = undefined
    }
  }

  private static hasLogChanged(newScheduledLog: ScheduledLog) {
    const oldLog = StandardRNOHLogger.recentLog
    if (oldLog === undefined) {
      return true
    }
    if (oldLog.formattedPath !== newScheduledLog.formattedPath) {
      return true
    }
    if (oldLog.offset !== newScheduledLog.offset) {
      return true
    }
    if (oldLog.severity !== newScheduledLog.severity) {
      return true
    }
    const newArgs = newScheduledLog.args
    if (newArgs.length !== oldLog.args.length) {
      return true
    }
    for (let i = 0; i < newArgs.length; i++) {
      if (newArgs[i] !== oldLog.args[i]) {
        return true
      }
    }
    return false
  }

  private static scheduledLog: ScheduledLog | undefined = undefined
  private static recentLog: ScheduledLog = undefined
  private static recentThrottlesCount: number = 0
  public static THROTTLE_IN_MS = 1000

  private formattedPath: string = ""
  private severityValueByName: Record<Severity, number> = {
    debug: 0,
    info: 1,
    warn: 2,
    error: 3,
    fatal: 4,
  }

  constructor(private minSeverity: Severity = "debug", protected pathSegments: string[] = [], protected tracer: Tracer | undefined = undefined) {
    const formattedPath = this.formatPathSegments(pathSegments)
    if (formattedPath) {
      this.formattedPath = `${formattedPath} `
    }
    if (!this.tracer) {
      this.tracer = new Tracer()
    }
  }

  public info(...args: any[]): void {
    this.log("info", this.getCurrentOffset(), ...args)
  }

  public warn(...args: any[]): void {
    this.log("warn", this.getCurrentOffset(), ...args)
  }

  public error(...args: any[]): void {
    this.log("error", this.getCurrentOffset(), ...args)
  }

  public fatal(...args: any[]): void {
    this.log("fatal", this.getCurrentOffset(), ...args)
  }

  public debug(...args: any[]): void {
    this.log("debug", this.getCurrentOffset(), ...args)
  }

  protected getDomain(): number {
    return 0xBEEF;
  }

  protected getTag(): string {
    return '#RNOH_ARK'
  }

  protected log(severity: Severity, offset: number, ...args: any[]): void {
    if (this.severityValueByName[severity] < this.severityValueByName[this.minSeverity]) {
      return;
    }
    if (args.length === 0) {
      args.push("")
    }
    StandardRNOHLogger.scheduleLog({
      args,
      offset,
      severity,
      formattedPath: this.formattedPath,
      createdAt: new Date(),
      logFn: (scheduledLog, throttlesCount) => {
        const formattedOffset = new Array(scheduledLog.offset).fill(" ").join("")
        const formattedLogRequestCounter = throttlesCount > 0 ? ` (x${throttlesCount + 1})` : ''
        hilog[severity](this.getDomain(), this.getTag(), `█__ ${formattedOffset}${scheduledLog.formattedPath}%{public}s${formattedLogRequestCounter}`, ...args)
      }
    })
  }


  private getCurrentOffset(): number {
    if (this.minSeverity !== "debug") {
      return 0
    }
    return this.tracer.getActiveTracesCount() * 2
  }

  public clone(pathSegment: string | string[]): RNOHLogger {
    const newPathSegments = Array.isArray(pathSegment) ? pathSegment : [pathSegment]
    return new StandardRNOHLogger(this.minSeverity, [...this.pathSegments, ...newPathSegments], this.tracer)
  }

  private formatPathSegments(pathSegments: string[]): string | null {
    if (pathSegments.length === 0) {
      return null
    }
    return pathSegments.join("::")
  }

  startTracing() {
    const startTime = Date.now()
    const currentOffset = this.getCurrentOffset()
    this.log("debug", currentOffset, "START")
    const stopTrace = this.tracer.startTrace(this.pathSegments.join('::'))
    return () => {
      stopTrace()
      const stopTime = Date.now()
      const durationInMs = stopTime - startTime
      this.log(durationInMs > 100 ? "warn" : "debug", currentOffset, `STOP (${durationInMs} ms)`)
    }
  }
}

