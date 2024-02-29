import { view_manager, RootView_manager } from 'libreact_arkui.so';

export class RootViewManager extends RootView_manager implements view_manager{
 
  constructor() {
	super("RootView");
	this.bindingArkTsParty(this);
  }
 
  getName(): string {
	return "RootView";
  }
}