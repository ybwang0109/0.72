import hilog from '@ohos.hilog';
import { UIManager } from './interface/UIManager';
import { UIManagerListener } from './interface/UIManagerListener';
import { LifecycleEventListener } from '../react/LifecycleEventListener';
import { ReactApplicationContext } from '../react/ReactApplicationContext';
import { RNOHFabricUIManager } from 'libreact_arkui.so'
import { ReactRoot } from '../react/ReactRoot';
import { MountingManager } from './mounting/MountingManager';
import { ViewManagerRegistry } from './ViewManagerRegistry'

import { FabricMountingManager } from './mounting/FabricMountingManager';

import type { AttributedString, ParagraphAttributes, LayoutConstrains } from "./TextLayoutManager";
import { measureParagraph } from "./TextLayoutManager"
import { ComponentFactory } from './ComponentFactory';

export class FabricUIManager implements UIManager, LifecycleEventListener {
  private mReactApplicationContext: ReactApplicationContext;
  private mRNOHFabricUIManager: RNOHFabricUIManager;
  private mMountingManager: MountingManager = new MountingManager();
  private mFabricMountingManager: FabricMountingManager;
  private mViewManagerRegistry: ViewManagerRegistry;
  private mComponentFactory: ComponentFactory;

  constructor(reactApplicationContext: ReactApplicationContext, componentFactory: ComponentFactory, viewManagerRegistry: ViewManagerRegistry) {
	this.mReactApplicationContext = reactApplicationContext;
	this.mViewManagerRegistry = viewManagerRegistry;
	this.mComponentFactory = componentFactory;

	this.mFabricMountingManager = new FabricMountingManager(this.mViewManagerRegistry);
	this.mRNOHFabricUIManager = new RNOHFabricUIManager(this.mFabricMountingManager);
	this.mRNOHFabricUIManager.registryMeasureTextFnRef((attributedString: AttributedString, paragraphAttributes: ParagraphAttributes, layoutConstraints: LayoutConstrains) => {
	  hilog.info(0x0000, 'reactOpenHarmony', 'FabricUIManager %{public}s', 'measureText');
	  try {
		const result = measureParagraph(attributedString, paragraphAttributes, layoutConstraints)
		return result
	  } catch (err) {
		console.error(err)
		throw new Error('measureText Error.');
	  }
	});

	this.mRNOHFabricUIManager.initializeScheduler(this.mComponentFactory);

  }

  startSurface(rootView: ReactRoot, moduleName: string, initialProps: string, widthMeasureSpec: number, heightMeasureSpec: number): number {

	hilog.info(0x0000, 'reactOpenHarmony', 'FabricUIManager %{public}s', 'startSurface');

	let rootTag: number = rootView.getRootViewTag();

	this.mMountingManager.startSurface(rootTag, rootView); //todo:原有流程，需要删除
	this.mFabricMountingManager.startSurface(1, rootView);

	this.mRNOHFabricUIManager.startSurfaceWithConstraints(
	  1,
	  "app_name", //如果是benchmark Bundle是"app_name"，如果是最早的测试Bundle是"rnempty"
	  {
		"foo": "bar",
		"concurrentRoot": true
	  },
	  384,
	  792,
	  0,
	  0,
	  3.5);

	return rootTag;
  }

  stopSurface(surfaceId: number): void {
	throw new Error('Method not implemented.');
  }

  updateRootLayoutSpecs(rootTag: number, widthMeasureSpec: number, heightMeasureSpec: number, offsetX: number, offsetY: number): void {
	throw new Error('Method not implemented.');
  }

  dispatchCommand(reactTag: number, commandId: string, commandArgs: string): void {
	throw new Error('Method not implemented.');
  }

  getEventDispatcher(): void {
	throw new Error('Method not implemented.');
  }

  synchronouslyUpdateViewOnUIThread(reactTag: number, props: string): void {
	throw new Error('Method not implemented.');
  }

  sendAccessibilityEvent(reactTag: number, eventType: number): void {
	throw new Error('Method not implemented.');
  }

  addUIManagerEventListener(listener: UIManagerListener): void {
	throw new Error('Method not implemented.');
  }

  removeUIManagerEventListener(listener: UIManagerListener): void {
	throw new Error('Method not implemented.');
  }

  resolveView(reactTag: number): View {
	throw new Error('Method not implemented.');
  }

  receiveEvent(surfaceId: number, reactTag: number, eventName: string, event: string): void {
	throw new Error('Method not implemented.');
  }

  initialize(): void {
	//
  }

  onCatalystInstanceDestroy(): void {
	throw new Error('Method not implemented.');
  }

  onHostResume(): void {
	throw new Error('Method not implemented.');
  }

  onHostPause(): void {
	throw new Error('Method not implemented.');
  }

  onHostDestroy(): void {
	throw new Error('Method not implemented.');
  }
}