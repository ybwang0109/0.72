import { Tag } from "./DescriptorBase"
import { DescriptorRegistry } from './DescriptorRegistry'
import { RNComponentCommandHub, RNOHComponentCommand } from "./RNComponentCommandHub"
import { RNOHLogger } from "./RNOHLogger"

type Origin = string

export class ResponderLockDispatcher {
  /**
   * Native responders can be blocked by React Native or by third-party packages like react-native-gesture-handler.
   * We need to keep locks by origin, because React Native can in some situations not release the lock for one component -
   * - that's why we use "boolean" instead of "number".
   */
  private isLockedByOriginByTag: Map<Tag, Map<Origin, boolean>> = new Map()
  private logger: RNOHLogger
  constructor(private descriptorRegistry: DescriptorRegistry, private componentCommandHub: RNComponentCommandHub, logger: RNOHLogger) {
    this.logger = logger.clone("ResponderLockDispatcher")
  }

  public onBlockResponder(tag: Tag, origin: Origin) {
    const tags = this.descriptorRegistry.getDescriptorLineage(tag).map(d => d.tag)
    tags.forEach((tag) => {
      const currentNumberOfLocks = this.getTotalNumberOfLocks(tag)
      if (currentNumberOfLocks === 0) {
        this.componentCommandHub.dispatchCommand(tag, RNOHComponentCommand.BLOCK_NATIVE_RESPONDER, undefined)
      }
      if (!this.isLockedByOriginByTag.has(tag)) {
        this.isLockedByOriginByTag.set(tag, new Map())
      }
      this.isLockedByOriginByTag.get(tag).set(origin, true)
    })
  }

  private getTotalNumberOfLocks(tag: Tag): number {
    const isLockedByOrigin = this.isLockedByOriginByTag.get(tag)
    if (!isLockedByOrigin) {
      return 0
    }
    return Array.from(isLockedByOrigin.values()).filter(isLocked => isLocked).length
  }

  public onUnblockResponder(tag: Tag, origin: Origin) {
    const tags = this.descriptorRegistry.getDescriptorLineage(tag).map(d => d.tag)
    tags.forEach((tag) => {
      const currentNumberOfLocks = this.getTotalNumberOfLocks(tag)
      if (currentNumberOfLocks === 0) {
        return;
      }
      this.isLockedByOriginByTag.get(tag).set(origin, false)
      const newNumberOfLocks = this.getTotalNumberOfLocks(tag)
      if (newNumberOfLocks === 0) {
        this.componentCommandHub.dispatchCommand(tag, RNOHComponentCommand.UNBLOCK_NATIVE_RESPONDER, undefined)
        this.isLockedByOriginByTag.delete(tag)
      }
    })
  }

}