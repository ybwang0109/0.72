import { JSIModuleProvider } from '../JSIModule/JSIModuleProvider';
import { UIManager } from './interface//UIManager';
import { ReactApplicationContext } from '../react/ReactApplicationContext';
import { ComponentFactory } from './ComponentFactory';
import { FabricUIManager } from './FabricUIManager';
import { ViewManagerRegistry } from './ViewManagerRegistry'

export class FabricJSIModuleProvider implements JSIModuleProvider<UIManager> {
  private mReactApplicationContext: ReactApplicationContext;
  private mViewManagerRegistry: ViewManagerRegistry;
  private mComponentFactory: ComponentFactory

  constructor(reactApplicationContext: ReactApplicationContext, componentFactory: ComponentFactory, viewManagerRegistry: ViewManagerRegistry) {
	this.mReactApplicationContext = reactApplicationContext;
	this.mViewManagerRegistry = viewManagerRegistry;
	this.mComponentFactory = componentFactory;
  }

  get(): UIManager {
	const uiManager: FabricUIManager = new FabricUIManager(this.mReactApplicationContext, this.mComponentFactory, this.mViewManagerRegistry);
	return uiManager;
  }
}