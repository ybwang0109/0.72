import { ReactRoot } from '../../react/ReactRoot';
import { ReactRootView } from '../../react/ReactRootView';

export class MountingManager {
  private mRootView: ReactRootView | null = null;

  constructor() {
  }

  public startSurface(surfaceId: number, rootView: ReactRoot ){
	this.mRootView = rootView as ReactRootView;

	//todo:创建一个SurfaceMountingManager，管理mTagToViewState，线性表。这个表怎么可以映射到RTNSurface上绑定。
	//ViewState为抽象节点
  }

}