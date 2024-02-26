import ArrayList from '@ohos.util.ArrayList';
import HashMap from '@ohos.util.HashMap';
import { view_manager } from 'libreact_arkui.so';

export class ViewManagerRegistry{
  private mViewManagers: HashMap<string, view_manager> = new HashMap<string, view_manager>();

  constructor(ViewManagerList: ArrayList<view_manager>) {
	for (let ViewManager of ViewManagerList) {
	  this.mViewManagers.set(ViewManager.getName(), ViewManager);
	}
  }

  public get(className: string): view_manager {
	let viewManager: view_manager = this.mViewManagers.get(className);
	return viewManager;
  }
}