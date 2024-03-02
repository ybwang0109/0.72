import { view_manager, RCTParagraph_manager } from 'libreact_arkui.so';

export class ReactParagraphManager extends RCTParagraph_manager implements view_manager {

  constructor() {
    super("Paragraph");
    this.bindingArkTsParty(this);
  }

  getName(): string {
    return "Paragraph";
  }
}