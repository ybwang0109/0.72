export const emitEvent: (a, b, c) => void

export class native_catalyst_instance {
  constructor(instanceName: string);
  initializeBridge(): void;
  loadScriptFromFile(fileName: string, sourceURL: string, loadSynchronously: boolean): void;
}

export class RNOHFabricUIManager {
  constructor(FabricMountingManager: any);
  initializeScheduler(ComponentFactory: component_factory): void;
  startSurfaceWithConstraints(): void;
  registryMutationCallback(mutationsListener: (mutations) => void): void;
  registryMeasureTextFnRef(measureTextFnRef: (attributedString, paragraphAttributes, layoutConstraints) => any): void;
  startSurfaceWithConstraints(surfaceId: number, moduleName: string, initialProps: any, width: number, height: number, viewportOffsetX: number, viewportOffsetY: number, pixelRatio: number): void;
}

export class turbo_module_manager {
  constructor(tmm: any, arkTsTurboModuleProviderRef: any);
  installJSIBindings(): void;
}

export abstract class fabric_mounting_manager{
  constructor();
  bindingArkTsParty(fabric_mounting_manager: fabric_mounting_manager);
  onSurfaceStart(surfaceId: number, surface_mounting_manager: surface_mounting_manager): void;
}

export abstract class surface_mounting_manager{
  constructor(surfaceId: number);
  bindingArkTsParty(surface_mounting_manager: surface_mounting_manager);
  registryViewManager(managerName: string, viewManager: view_manager);
  attachRootViewToWindow();
}

export class component_factory{
  constructor();
}

export class default_components_registry{
  constructor(ComponentFactory: component_factory);
}

export interface view_manager {
  getName(): string;
}

export abstract class RootView_manager{
  constructor(componentName: string);
  bindingArkTsParty(view_manager: RootView_manager);
}

export abstract class RCTView_manager{
  constructor(componentName: string);
  bindingArkTsParty(view_manager: RCTView_manager);
}

export abstract class RCTParagraph_manager{
  constructor(componentName: string);
  bindingArkTsParty(view_manager: RCTParagraph_manager);
}

export abstract class RCTScrollView_manager{
  constructor(componentName: string);
  bindingArkTsParty(view_manager: RCTScrollView_manager);
}