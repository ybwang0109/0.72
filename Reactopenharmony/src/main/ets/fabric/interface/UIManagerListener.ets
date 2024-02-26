import {UIManager} from "./UIManager"

/** Listener used to hook into the UIManager update process. */
export interface UIManagerListener {
  /**
   * Called right before view updates are dispatched at the end of a batch. This is useful if a
   * module needs to add UIBlocks to the queue before it is flushed.
   *
   * <p>This is called by Paper only.
   */
  willDispatchViewUpdates(uiManager: UIManager): void;
  /**
   * Called on UIThread right before view updates are executed.
   *
   * <p>This is called by Fabric only.
   */
  willMountItems(uiManager: UIManager): void;
  /**
   * Called on UIThread right after view updates are executed.
   *
   * <p>This is called by Fabric only.
   */
  didMountItems(uiManager: UIManager): void;
  /**
   * Called on UIThread right after view updates are dispatched for a frame. Note that this will be
   * called for every frame even if there are no updates.
   *
   * <p>This is called by Fabric only.
   */
  didDispatchMountItems(uiManager: UIManager): void;
  /**
   * Called right after scheduleMountItems is called in Fabric, after a new tree is committed.
   *
   * <p>This is called by Fabric only.
   */
  didScheduleMountItems(uiManager: UIManager): void;
}
