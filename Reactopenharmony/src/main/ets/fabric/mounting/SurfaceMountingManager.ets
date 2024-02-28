import { surface_mounting_manager, view_manager } from 'libreact_arkui.so';
import { ReactRoot } from '../../react/ReactRoot';
import { ViewManagerRegistry } from '../ViewManagerRegistry'
import hilog from '@ohos.hilog';

export class SurfaceMountingManager extends surface_mounting_manager {
  private mViewManagerRegistry: ViewManagerRegistry;
  private mJSResponderHandler = undefined; //还不知道是干什么用的需要注册给一个view

  constructor(surfaceId: number, viewManagerRegistry: ViewManagerRegistry, rootView: ReactRoot) {
    super(surfaceId);
    this.bindingArkTsParty(this);
    this.mViewManagerRegistry = viewManagerRegistry;

    this.registryViewManager("View", this.mViewManagerRegistry.get("View"));
    this.registryViewManager("Paragraph", this.mViewManagerRegistry.get("Paragraph"));
    this.registryViewManager("ScrollView", this.mViewManagerRegistry.get("ScrollView"));

  }

  // todo:这个方法没有调通，先用registryViewManager代替
  public getViemManager(componentName: string): view_manager | null {
    hilog.info(0x0000, "view_manager", ' componentName = %{public}s', componentName);
    return null;
  }
}