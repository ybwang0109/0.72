import ArrayList from '@ohos.util.ArrayList';
import { JSIModulePackage } from '../JSIModule/JSIModulePackage';
import { JSIModuleSpec } from '../JSIModule/JSIModuleSpec';
import { ReactApplicationContext } from '../react/ReactApplicationContext';
import { ReactNativeHost } from '../react/ReactNativeHost';
import { UIManager } from '../fabric/interface/UIManager';
import { TurboModuleManager } from '../JSIModule/TurboModuleManager';
import { JSIModuleProvider } from '../JSIModule/JSIModuleProvider';
import { JSIModuleType } from '../JSIModule/JSIModuleType';
import { JSIModule } from '../JSIModule/JSIModule';
import { FabricJSIModuleProvider } from '../fabric/FabricJSIModuleProvider';
import { ViewManagerRegistry } from '../fabric/ViewManagerRegistry';
import { createViewManagers } from '../react_core_package/views/ViewManagers';
import { ComponentFactory } from '../fabric/ComponentFactory';
import { DefaultComponentsRegistry } from './DefaultComponentsRegistry';


export class DefaultJSIModulePackage implements JSIModulePackage {
  private mReactNativeHost: ReactNativeHost;

  constructor(reactNativeHost: ReactNativeHost) {
    this.mReactNativeHost = reactNativeHost;
  }

  getImportPath(): string {
    return "ReactOpenHarmony/src/main/ets/defaults/DefaultJSIModulePackage.ets";
  }

  getJSIModules(reactApplicationContext: ReactApplicationContext): ArrayList<JSIModuleSpec<JSIModule>> {
    const jsiModuleSpecList: ArrayList<JSIModuleSpec<JSIModule>> = new ArrayList<JSIModuleSpec<JSIModule>>();
    jsiModuleSpecList.add(new JSIModuleSpecForFabric(reactApplicationContext, this.mReactNativeHost));
    jsiModuleSpecList.add(new JSIModuleSpecForTurboModule(reactApplicationContext, this.mReactNativeHost));
    return jsiModuleSpecList;
  }
}

class JSIModuleSpecForFabric implements JSIModuleSpec<UIManager> {
  private mReactApplicationContext: ReactApplicationContext;
  private mReactNativeHost: ReactNativeHost;

  constructor(reactApplicationContext: ReactApplicationContext, reactNativeHost: ReactNativeHost) {
    this.mReactApplicationContext = reactApplicationContext;
    this.mReactNativeHost = reactNativeHost;
  }

  getImportPath(): string {
    return "ReactOpenHarmony/src/main/ets/defaults/DefaultJSIModulePackage.ets";
  }

  getJSIModuleType(): JSIModuleType {
    return JSIModuleType.UIManager;
  }

  getJSIModuleProvider(): JSIModuleProvider<UIManager> {
    let componentFactory: ComponentFactory = new ComponentFactory();
    new DefaultComponentsRegistry(componentFactory);

    let viewManagers = createViewManagers(); //todo: 从reactNativeHost.reactInstanceManager.getOrCreateViewManagers(reactApplicationContext)获取。
    let viewManagerRegistry = new ViewManagerRegistry(viewManagers);


    return new FabricJSIModuleProvider(this.mReactApplicationContext, componentFactory, viewManagerRegistry);
  }
}

class JSIModuleSpecForTurboModule implements JSIModuleSpec<TurboModuleManager> {
  private mReactApplicationContext: ReactApplicationContext;
  private mReactNativeHost: ReactNativeHost;

  constructor(
    reactApplicationContext: ReactApplicationContext,
    reactNativeHost: ReactNativeHost
  ) {
    this.mReactApplicationContext = reactApplicationContext;
    this.mReactNativeHost = reactNativeHost;
  }

  getJSIModuleType(): JSIModuleType {
    return JSIModuleType.TurboModuleManager;
  }

  getJSIModuleProvider(): JSIModuleProvider<TurboModuleManager> {
    throw new Error('getJSIModuleProvider Method not implemented.');
  }
}

