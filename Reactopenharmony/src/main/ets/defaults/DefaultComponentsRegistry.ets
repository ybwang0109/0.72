import { default_components_registry } from 'libreact_arkui.so';
import { ComponentFactory } from '../fabric/ComponentFactory';

export class DefaultComponentsRegistry extends default_components_registry {
  constructor(componentFactory: ComponentFactory) {
	super(componentFactory);
  }
}