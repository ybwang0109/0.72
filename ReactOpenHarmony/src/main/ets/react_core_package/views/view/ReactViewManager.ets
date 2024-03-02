import { view_manager, RCTView_manager } from 'libreact_arkui.so';

export class ReactViewManager extends RCTView_manager implements view_manager {

  constructor() {
    super("View");
    this.bindingArkTsParty(this);
  }

  getName(): string {
    return "View";
  }
}