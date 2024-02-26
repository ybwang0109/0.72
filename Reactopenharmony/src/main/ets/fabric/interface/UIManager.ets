import { ReactRoot } from '../../react/ReactRoot';
import { JSIModule } from "../../JSIModule/JSIModule"
import {UIManagerListener} from "./UIManagerListener"

export interface UIManager extends JSIModule {

  /** Registers a new root view with width and height. */
  startSurface(
	rootView: ReactRoot,
	moduleName: string,
	initialProps: string,
	widthMeasureSpec: number,
	heightMeasureSpec: number): number;

  /**
   * Stop a surface from running in JS and clears up native memory usage. Assumes that the native
   * View hierarchy has already been cleaned up. Fabric-only.
   */
  stopSurface(surfaceId: number): void;

  /**
   * Updates the layout specs of the RootShadowNode based on the Measure specs received by
   * parameters. offsetX and offsetY are the position of the RootView within the screen.
   */
  updateRootLayoutSpecs(
	rootTag: number, widthMeasureSpec: number, heightMeasureSpec: number, offsetX: number, offsetY: number): void;

  /**
   * Dispatches the commandId received by parameter to the view associated with the reactTag. The
   * command will be processed in the UIThread.
   *
   * <p>Pre-Fabric, this is only called on the Native Module Thread.
   *
   * @param reactTag {@link int} that identifies the view that will receive this command
   * @param commandId {@link String} command id
   * @param commandArgs {@link ReadableArray} parameters associated with the command
   */
  dispatchCommand(reactTag: number, commandId: string, commandArgs: string): void;

  /** @return the {@link EventDispatcher} object that is used by this class. */
  getEventDispatcher(): void;

  /**
   * Used by native animated module to bypass the process of updating the values through the shadow
   * view hierarchy. This method will directly update native views, which means that updates for
   * layout-related propertied won't be handled properly. Make sure you know what you're doing
   * before calling this method :)
   *
   * @param reactTag {@link int} that identifies the view that will be updated
   * @param props {@link ReadableMap} props that should be immediately updated in view
   */
  synchronouslyUpdateViewOnUIThread(reactTag: number, props: string): void;

  /**
   * Dispatch an accessibility event to a view asynchronously.
   *
   * <p>Pre-Fabric, this is only called on the Native Module Thread.
   *
   * @param reactTag
   * @param eventType
   */
  sendAccessibilityEvent(reactTag: number, eventType: number): void;

  /**
   * Register a {@link UIManagerListener} with this UIManager to receive lifecycle callbacks.
   *
   * @param listener
   */
  addUIManagerEventListener(listener: UIManagerListener): void;

  /**
   * Unregister a {@link UIManagerListener} from this UIManager to stop receiving lifecycle
   * callbacks.
   *
   * @param listener
   */
  removeUIManagerEventListener(listener: UIManagerListener): void;

  /**
   * Resolves a view based on its reactTag. Do not mutate properties on this view that are already
   * managed by React, as there are no guarantees this changes will be preserved.
   *
   * @throws IllegalViewOperationException if tag could not be resolved.
   * @param reactTag tag
   * @return view if found
   */
  resolveView(reactTag: number): View;

  /**
   * This method dispatches events from RN Android code to JS. The delivery of this event will not
   * be queued in EventDispatcher class.
   *
   * @param surfaceId
   * @param reactTag tag
   * @param eventName name of the event
   * @param event parameters
   */
  receiveEvent(surfaceId: number, reactTag: number, eventName: string, event: string): void;


}