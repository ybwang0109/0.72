import hilog from '@ohos.hilog';
import { fabric_mounting_manager } from 'libreact_arkui.so'
import { ReactRoot } from '../../react/ReactRoot';
import { SurfaceMountingManager } from './SurfaceMountingManager';
import { ViewManagerRegistry } from '../ViewManagerRegistry'
import { RootViewManager } from '../RootViewManager'
import { ReactApplicationContext } from '../../react/ReactApplicationContext';

export class FabricMountingManager extends fabric_mounting_manager {
  private mViewManagerRegistry: ViewManagerRegistry;
  private mRootViewManager: RootViewManager = new RootViewManager();
  constructor(viewManagerRegistry: ViewManagerRegistry) {
    super();
    this.bindingArkTsParty(this);
    this.mViewManagerRegistry = viewManagerRegistry;
  };

  public startSurface(surfaceId: number, reactApplicationContext: ReactApplicationContext, rootView: ReactRoot): SurfaceMountingManager {
    hilog.info(0x0000, "fabric_mounting_manager", ' surfaceId = %{public}s', surfaceId);

    let surfaceMountingManager: SurfaceMountingManager = new SurfaceMountingManager(surfaceId, this.mViewManagerRegistry, this.mRootViewManager, reactApplicationContext);
    this.onSurfaceStart(surfaceId, surfaceMountingManager);

    if (rootView != null) {
      surfaceMountingManager.attachRootView(rootView, reactApplicationContext);
    }

    return surfaceMountingManager;
  }
}