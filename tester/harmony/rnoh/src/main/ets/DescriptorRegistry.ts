import {Tag, Descriptor} from './descriptor';
import {MutationType, Mutation} from './mutations';

type SubtreeListener = () => void;
export class DescriptorRegistry {
  private descriptorByTag: Record<Tag, Descriptor>;
  private descriptorListenersSetByTag: Map<
    Tag,
    Set<(descriptor: Descriptor) => void>
  > = new Map();
  private subtreeListenersSetByTag: Map<Tag, Set<SubtreeListener>> = new Map();

  constructor(descriptorByTag: Record<Tag, Descriptor>) {
    this.descriptorByTag = descriptorByTag;
  }

  public getDescriptor<TDescriptor extends Descriptor>(tag: Tag): TDescriptor {
    return this.descriptorByTag[tag.toString()] as TDescriptor;
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
        // NOTE: we use the spread operator here, to create a shallow
        // copy of the descriptor object. This will cause the subscribed
        // component to update
        cb({...updatedDescriptor});
      });
    });
    this.callSubtreeListeners(uniqueUpdated);
  }

  private callSubtreeListeners(updatedDescriptorTags: Tag[]) {
    const setOfSubtreeListenersToCall = new Set<SubtreeListener>();
    for (const tag of updatedDescriptorTags) {
      let descriptor = this.descriptorByTag[tag];
      while (descriptor) {
        if (this.subtreeListenersSetByTag.has(descriptor.tag)) {
          for (const listener of this.subtreeListenersSetByTag.get(
            descriptor.tag,
          )) {
            setOfSubtreeListenersToCall.add(listener);
          }
        }
        if (descriptor.parentTag) {
          descriptor = this.descriptorByTag[descriptor.parentTag];
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
    this.descriptorListenersSetByTag.get(tag).add(listener);
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
    if (callbacksSet.size === 0) {
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
    this.subtreeListenersSetByTag.get(rootTag).add(listener);

    return () => {
      const callbacksSet = this.descriptorListenersSetByTag.get(rootTag);
      callbacksSet?.delete(listener);
      if (callbacksSet.size === 0) {
        this.descriptorListenersSetByTag.delete(rootTag);
      }
    };
  }

  private applyMutation(mutation: Mutation): Tag[] {
    if (mutation.type === MutationType.CREATE) {
      this.descriptorByTag[mutation.descriptor.tag] = mutation.descriptor;
      return [];
    } else if (mutation.type === MutationType.INSERT) {
      this.descriptorByTag[mutation.childTag].parentTag = mutation.parentTag;
      this.descriptorByTag[mutation.parentTag].childrenTags.push(
        mutation.childTag,
      );
      return [mutation.childTag, mutation.parentTag];
    } else if (mutation.type === MutationType.UPDATE) {
      const currentDescriptor = this.descriptorByTag[mutation.descriptor.tag];
      const children = currentDescriptor.childrenTags;
      this.descriptorByTag[mutation.descriptor.tag] = {
        ...currentDescriptor,
        ...mutation.descriptor,
      };
      this.descriptorByTag[mutation.descriptor.tag].childrenTags = children;
      return [mutation.descriptor.tag];
    } else if (mutation.type === MutationType.REMOVE) {
      const parentDescriptor = this.descriptorByTag[mutation.parentTag];
      const idx = parentDescriptor.childrenTags.indexOf(mutation.childTag);
      if (idx != -1) {
        parentDescriptor.childrenTags.splice(idx, 1);
      }
      return [mutation.parentTag];
    } else if (mutation.type === MutationType.DELETE) {
      delete this.descriptorByTag[mutation.tag];
      return [];
    } else if (mutation.type === MutationType.REMOVE_DELETE_TREE) {
      return [];
    }
    return [];
  }
}
