import { Tag, Descriptor } from './DescriptorBase';
import { MutationType, Mutation } from './Mutation';

type SubtreeListener = () => void;
export class DescriptorRegistry {
  private descriptorByTag: Map<Tag, Descriptor>;
  private descriptorListenersSetByTag: Map<Tag, Set<(descriptor: Descriptor) => void>> = new Map();
  private subtreeListenersSetByTag: Map<Tag, Set<SubtreeListener>> = new Map();

  constructor(descriptorByTag: Record<Tag, Descriptor>) {
    this.descriptorByTag = new Map();
    for (const tag in descriptorByTag) {
      this.descriptorByTag.set(parseInt(tag), descriptorByTag[tag])
    }
  }

  public getDescriptor<TDescriptor extends Descriptor>(tag: Tag): TDescriptor {
    return this.descriptorByTag.get(tag) as TDescriptor;
  }

  public applyMutations(mutations: Mutation[]) {
    const updatedComponents = mutations.flatMap(mutation =>
      this.applyMutation(mutation),
    );
    const uniqueUpdated = [...new Set(updatedComponents)];
    uniqueUpdated.forEach(tag => {
      const updatedDescriptor = this.getDescriptor(tag);
      if (!updatedDescriptor) return;
      this.descriptorListenersSetByTag.get(tag)?.forEach(cb => {
        cb(updatedDescriptor)
      });
    });
    this.callSubtreeListeners(uniqueUpdated);
  }

  private callSubtreeListeners(updatedDescriptorTags: Tag[]) {
    const setOfSubtreeListenersToCall = new Set<SubtreeListener>();
    for (const tag of updatedDescriptorTags) {
      let descriptor = this.descriptorByTag.get(tag);
      while (descriptor) {
        const listeners = this.subtreeListenersSetByTag.get(descriptor.tag);
        if (listeners) {
          for (const listener of listeners) {
            setOfSubtreeListenersToCall.add(listener);
          }
        }
        if (descriptor.parentTag) {
          descriptor = this.descriptorByTag.get(descriptor.parentTag);
        } else {
          break;
        }
      }
    }
    setOfSubtreeListenersToCall.forEach(listener => {
      listener();
    });
  }

  public subscribeToDescriptorChanges(
    tag: Tag,
    listener: (descriptor: Descriptor) => void,
  ) {
    if (!this.descriptorListenersSetByTag.has(tag)) {
      this.descriptorListenersSetByTag.set(tag, new Set());
    }
    this.descriptorListenersSetByTag.get(tag)!.add(listener);
    return () => {
      this.removeDescriptorChangesListener(tag, listener);
    };
  }

  private removeDescriptorChangesListener(
    tag: Tag,
    listener: (descriptor: Descriptor) => void,
  ) {
    const callbacksSet = this.descriptorListenersSetByTag.get(tag);
    callbacksSet?.delete(listener);
    if (callbacksSet?.size === 0) {
      this.descriptorListenersSetByTag.delete(tag);
    }
  }

  public subscribeToDescriptorSubtreeChanges(
    rootTag: Tag,
    listener: SubtreeListener,
  ) {
    if (!this.subtreeListenersSetByTag.has(rootTag)) {
      this.subtreeListenersSetByTag.set(rootTag, new Set());
    }
    this.subtreeListenersSetByTag.get(rootTag)!.add(listener);

    return () => {
      const callbacksSet = this.descriptorListenersSetByTag.get(rootTag);
      callbacksSet?.delete(listener);
      if (callbacksSet?.size === 0) {
        this.descriptorListenersSetByTag.delete(rootTag);
      }
    };
  }

  private applyMutation(mutation: Mutation): Tag[] {
    if (mutation.type === MutationType.CREATE) {
      this.descriptorByTag.set(mutation.descriptor.tag, mutation.descriptor);
      return [];
    } else if (mutation.type === MutationType.INSERT) {
      this.descriptorByTag.get(mutation.childTag).parentTag = mutation.parentTag;
      this.descriptorByTag.get(mutation.parentTag).childrenTags.push(
        mutation.childTag,
      );
      return [mutation.childTag, mutation.parentTag];
    } else if (mutation.type === MutationType.UPDATE) {
      const currentDescriptor = this.descriptorByTag.get(mutation.descriptor.tag);
      const children = currentDescriptor.childrenTags;
      this.descriptorByTag.set(mutation.descriptor.tag, {
        ...currentDescriptor,
        ...mutation.descriptor,
      });
      this.descriptorByTag.get(mutation.descriptor.tag).childrenTags = children;
      return [mutation.descriptor.tag];
    } else if (mutation.type === MutationType.REMOVE) {
      const parentDescriptor = this.descriptorByTag.get(mutation.parentTag);
      const idx = parentDescriptor.childrenTags.indexOf(mutation.childTag);
      if (idx != -1) {
        parentDescriptor.childrenTags.splice(idx, 1);
      }
      this.descriptorByTag.get(mutation.childTag).parentTag = undefined;
      return [mutation.parentTag];
    } else if (mutation.type === MutationType.DELETE) {
      this.descriptorByTag.delete(mutation.tag);
      return [];
    } else if (mutation.type === MutationType.REMOVE_DELETE_TREE) {
      return [];
    }
    return [];
  }
}