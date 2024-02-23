import { view_manager, RCTScrollView_manager } from 'libreact_arkui.so';

export class ReactScrollViewManager extends RCTScrollView_manager implements view_manager{

  constructor() {
	super("ScrollView");
	this.bindingArkTsParty(this);
  }

  getName(): string {
	return "ScrollView";
  }
}