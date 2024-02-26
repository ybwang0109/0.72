import hilog from '@ohos.hilog';
import { fabric_mounting_manager } from 'libreact_arkui.so'
import { ReactRoot } from '../../react/ReactRoot';
import { SurfaceMountingManager } from './SurfaceMountingManager';
import { ViewManagerRegistry } from '../ViewManagerRegistry'

export class FabricMountingManager extends fabric_mounting_manager {
  private mViewManagerRegistry: ViewManagerRegistry;
  constructor(viewManagerRegistry: ViewManagerRegistry) {
	super();
	this.bindingArkTsParty(this);
	this.mViewManagerRegistry = viewManagerRegistry;
  };

  public startSurface(surfaceId: number, rootView: ReactRoot): SurfaceMountingManager {
	hilog.info(0x0000, "fabric_mounting_manager", ' surfaceId = %{public}s', surfaceId);

	let surfaceMountingManager: SurfaceMountingManager = new SurfaceMountingManager(surfaceId, this.mViewManagerRegistry, rootView);
	this.onSurfaceStart(surfaceId, surfaceMountingManager);
	return surfaceMountingManager;
  }
}