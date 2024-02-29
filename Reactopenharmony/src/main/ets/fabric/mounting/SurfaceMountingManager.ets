import { surface_mounting_manager, view_manager } from 'libreact_arkui.so';
import { ReactRoot } from '../../react/ReactRoot';
import { ViewManagerRegistry } from '../ViewManagerRegistry'
import hilog from '@ohos.hilog';
import { ReactApplicationContext } from '../../react/ReactApplicationContext';
import { RootViewManager } from '../RootViewManager';

export class SurfaceMountingManager extends surface_mounting_manager {
  private mViewManagerRegistry: ViewManagerRegistry;
  private mRootViewManager: RootViewManager;
	private mReactApplicationContext: ReactApplicationContext;
  private mJSResponderHandler = undefined; //还不知道是干什么用的需要注册给一个view
  private mRootView: ReactRoot | null = null;

  constructor(surfaceId: number, viewManagerRegistry:ViewManagerRegistry, rootViewManager: RootViewManager, reactApplicationContext: ReactApplicationContext) {
    super(surfaceId);
    this.bindingArkTsParty(this);
    this.mViewManagerRegistry = viewManagerRegistry;
    this.mRootViewManager = rootViewManager;
		this.mReactApplicationContext = reactApplicationContext;

    this.registryViewManager("RootView", rootViewManager);
    this.registryViewManager("View", this.mViewManagerRegistry.get("View"));
    this.registryViewManager("Paragraph", this.mViewManagerRegistry.get("Paragraph"));
    this.registryViewManager("ScrollView", this.mViewManagerRegistry.get("ScrollView"));

  }

	public attachRootView(rootView: ReactRoot, reactApplicationContext: ReactApplicationContext): void {
		this.mReactApplicationContext = reactApplicationContext;
		this.mRootView = rootView;
		this.attachRootViewToWindow();
	}

  // todo:这个方法没有调通，先用registryViewManager代替
  public getViemManager(componentName: string): view_manager | null {
    hilog.info(0x0000, "view_manager", ' componentName = %{public}s', componentName);
    return null;
  }
  
}