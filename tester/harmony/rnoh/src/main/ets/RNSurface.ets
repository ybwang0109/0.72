import { ComponentBuilderContext, CustomComponentBuilder,
  rnComponentFactoryBuilder } from './RNOHCorePackage/components/RNComponentFactory';
import { RNComponentFactory } from './RNOHCorePackage';
import { Descriptor, DisplayMode, RNOHContext, RNOHLogger, Tag } from './RNOH';
import {
  ViewBaseProps,
  ViewDescriptorWrapperBase,
  ViewRawProps,
  ViewDescriptorWrapper
} from './RNOHCorePackage/components/RNViewBase';
import { TouchDispatcher } from './RNOH/TouchDispatcher';
import { SurfaceHandle, SurfaceProps } from './RNOH/SurfaceHandle';

interface RootViewState {}

export type RootDescriptor = Descriptor<"RootView", ViewBaseProps, RootViewState, ViewRawProps>;

interface SurfaceConfig1 {
  surfaceHandle: SurfaceHandle
}

interface SurfaceConfig2 {
  appKey: string,
  initialProps: SurfaceProps,
}

type SurfaceConfig = SurfaceConfig1 | SurfaceConfig2

export class BuilderProxy {
  public static buildCustomComponent: CustomComponentBuilder;
}

@Component
export struct RNSurface {
  ctx!: RNOHContext;
  surfaceConfig!: SurfaceConfig;
  @BuilderParam buildCustomComponent: (ctx: ComponentBuilderContext) => void;
  surfaceWidth: number = 0;
  surfaceHeight: number = 0;
  surfaceOffsetX: number = 0;
  surfaceOffsetY: number = 0;
  @State descriptor: RootDescriptor = Object() as RootDescriptor;
  @State descriptorWrapper: ViewDescriptorWrapperBase | undefined = undefined
  @State private shouldStartSurface: boolean = false;
  private surfaceHandle!: SurfaceHandle;
  private cleanUpCallbacks: (() => void)[] = [];
  private touchDispatcher!: TouchDispatcher;
  private shouldStopSurface: boolean = false;
  private initialProps!: SurfaceProps;
  private logger!: RNOHLogger

  aboutToAppear() {
    this.logger = this.ctx.logger.clone("RNSurface")
    BuilderProxy.buildCustomComponent = this.buildCustomComponent
    const stopTracing = this.logger.clone("aboutToAppear").startTracing()
    if (Object.keys(this.surfaceConfig).includes("surfaceHandle")) {
      this.surfaceHandle = (this.surfaceConfig as Object as SurfaceConfig1).surfaceHandle;
      this.surfaceHandle.setDisplayMode(DisplayMode.Visible);
    } else {
      this.surfaceHandle = this.ctx.rnInstance.createSurface((this.surfaceConfig as Object as SurfaceConfig2).appKey);
      this.initialProps = (this.surfaceConfig as Object as SurfaceConfig2).initialProps;
      this.shouldStartSurface = true;
      this.shouldStopSurface = true;
    }
    const tag = this.surfaceHandle.getTag();
    this.onUpdateComponent(this.ctx.rnInstance.descriptorRegistry.getDescriptor(tag))
    this.touchDispatcher = new TouchDispatcher(tag, this.ctx.rnInstance, this.ctx.logger)
    this.cleanUpCallbacks.push(this.ctx.descriptorRegistry.subscribeToDescriptorChanges(
      tag,
      (newDescriptor) => this.onUpdateComponent(newDescriptor)
    ))
    stopTracing()
  }

  aboutToDisappear() {
    const stopTracing = this.logger.clone("aboutToDisappear").startTracing()
    this.cleanUpCallbacks.forEach(cb => cb())
    if (this.shouldStopSurface) {
      this.surfaceHandle.stop().then(() => {
        this.surfaceHandle.destroy();
      })
    } else if (this.surfaceHandle.getDisplayMode() === DisplayMode.Visible) {
      this.surfaceHandle.setDisplayMode(DisplayMode.Suspended);
    }
    stopTracing()
  }

  onUpdateComponent(newDescriptor: Descriptor) {
    this.descriptor = newDescriptor as RootDescriptor
    this.descriptorWrapper = new ViewDescriptorWrapper(newDescriptor)
  }

  handleAreaChange(_oldValue: Area, newValue: Area) {
    const stopTracing = this.logger.clone("handleAreaChange").startTracing()
    this.surfaceWidth = newValue.width as number
    this.surfaceHeight = newValue.height as number
    this.surfaceOffsetX = newValue.globalPosition.x as number
    this.surfaceOffsetY = newValue.globalPosition.y as number
    this.updateSurfaceConstraints()
    stopTracing()
  }

  updateSurfaceConstraints() {
    if (this.shouldStartSurface) {
      this.surfaceHandle.start(
        {
          width: this.surfaceWidth,
          height: this.surfaceHeight,
          surfaceOffsetX: this.surfaceOffsetX,
          surfaceOffsetY: this.surfaceOffsetY,
          pixelRatio: vp2px(1)
        },
        this.initialProps).then(() => {
        this.surfaceHandle.setDisplayMode(DisplayMode.Visible)
      })
      this.shouldStartSurface = false

    } else {
      this.surfaceHandle.updateConstraints({
        width: this.surfaceWidth,
        height: this.surfaceHeight,
        surfaceOffsetX: this.surfaceOffsetX,
        surfaceOffsetY: this.surfaceOffsetY,
        pixelRatio: vp2px(1),
      });
    }
  }

  handleTouch(event?: TouchEvent) {
    this.logger.clone("handleTouch").debug()
    this.touchDispatcher.handleTouchEvent(event)

  }

  build() {
    Stack() {
      // RNComponentFactory({
      //   ctx: this.ctx,
      //   tag: this.surfaceHandle.getTag(),
      //   buildCustomComponent: this.buildCustomComponent
      // })

      ForEach(this.descriptor.childrenTags, (childrenTag: Tag) => {
        // RNComponentFactory({ ctx: this.ctx, tag: childrenTag, buildCustomComponent: this.buildCustomComponent })
        rnComponentFactoryBuilder(this.ctx, childrenTag, this.ctx.rnInstance.getComponentNameFromDescriptorType(this.ctx.descriptorRegistry.getDescriptor(childrenTag)?.type))
      }, (childrenTag: Tag) => childrenTag.toString())
    }
    .width("100%")
    .height("100%")
    .onAreaChange((oldArea, newArea) => this.handleAreaChange(oldArea, newArea))
    .onTouch((e) => this.handleTouch(e))
  }
}
