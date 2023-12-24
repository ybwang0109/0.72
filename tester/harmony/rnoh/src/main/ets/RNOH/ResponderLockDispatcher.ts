import { Tag } from "./DescriptorBase"
import { DescriptorRegistry } from './DescriptorRegistry'
import { RNComponentCommandHub, RNOHComponentCommand } from "./RNComponentCommandHub"
import { RNOHLogger } from "./RNOHLogger"

export class ResponderLockDispatcher {
  private numberOfLocksByTag: Map<Tag, number> = new Map()
  private logger: RNOHLogger
  constructor(private componentManagerRegistry: ComponentManagerRegistry, private componentCommandHub: RNComponentCommandHub, logger: RNOHLogger) {
    this.logger = logger.clone("ResponderLockDispatcher")
  }

  public onBlockResponder(tag: Tag) {
    const tags = this.descriptorRegistry.getDescriptorLineage(tag).map(d => d.tag)
    tags.forEach((tag) => {
      const currentNumberOfLocks = this.numberOfLocksByTag.get(tag) ?? 0
      if (currentNumberOfLocks === 0) {
        this.componentCommandHub.dispatchCommand(tag, RNOHComponentCommand.BLOCK_NATIVE_RESPONDER, undefined)
      }
      this.numberOfLocksByTag.set(tag, currentNumberOfLocks + 1)
    })
  }

  public onUnblockResponder(tag: Tag) {
    const stopTracing = this.logger.clone("onUnblockResponder").startTracing()
    const tags = this.descriptorRegistry.getDescriptorLineage(tag).map(d => d.tag)
    tags.forEach((tag) => {
      const currentNumberOfLocks = this.numberOfLocksByTag.get(tag) ?? 0
      if (currentNumberOfLocks === 0) {
        return;
      }
      const newNumberOfLocks = currentNumberOfLocks - 1
      this.numberOfLocksByTag.set(tag, newNumberOfLocks)
      if (newNumberOfLocks === 0) {
        this.componentCommandHub.dispatchCommand(tag, RNOHComponentCommand.UNBLOCK_NATIVE_RESPONDER, undefined)
        this.numberOfLocksByTag.delete(tag)
      }
    })
    stopTracing()
  }
}