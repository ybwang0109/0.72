import { RNViewManager } from '../..';
import matrix4 from '@ohos.matrix4';
import { convertColorSegmentsToString, RNOHContext, DEFAULT_LINE_SPACING, TransformMatrix, } from '../../../RNOH'
import { RNViewBase, ViewBaseDescriptor, ViewDescriptorWrapper } from '../RNViewBase'
import {
  stringToFontStyle,
  getTextDecorationLine,
  stringToAlignment,
  stringToVerticalAlign,
  stringToTextTransform,
  getLetterSpacing,
  getMaxLines,
  ellipsizeModeToTextOverflow,
  getTextShadow,
  capitalizeTextIfNecessary,
} from './conversions'
import { AttributedFragment } from './types';
import { TextDescriptor } from './types'

@Component
export struct RNSimpleText {
  ctx!: RNOHContext
  tag: number = 0
  @State descriptor: TextDescriptor = {} as TextDescriptor
  @State fragment: AttributedFragment | undefined = undefined
  private unregisterDescriptorChangesListener?: () => void = undefined

  public componentManager!: RNViewManager;
  @State private descriptorWrapper: ViewDescriptorWrapper | undefined = undefined
  private unregisterComponentManager?: () => void = undefined
  private unregisterCommandCallback?: () => void = undefined

  aboutToAppear() {
    this.initComponent();
    const descriptor = this.ctx.descriptorRegistry.getDescriptor<TextDescriptor>(this.tag)
    this.updateDescriptor(descriptor);
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.updateDescriptor(newDescriptor as TextDescriptor)
        this.setDescriptor(newDescriptor)
      }
    )
  }

  updateDescriptor(newDescriptor: TextDescriptor) {
    this.descriptor = newDescriptor
    this.fragment = newDescriptor.props.fragments[0]
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.()

    this.unregisterComponentManager?.()
    this.unregisterCommandCallback?.()
  }

  initComponent() {
    let descriptor = this.ctx.descriptorRegistry.getDescriptor<ViewBaseDescriptor>(this.tag)
    if (!this.componentManager) {
      this.componentManager = new RNViewManager(this.tag, this.ctx)
    }
    this.unregisterComponentManager = this.ctx.componentManagerRegistry.registerComponentManager(this.tag, this.componentManager)
    this.setDescriptor(descriptor)
    const parentTag = descriptor.parentTag;
    this.componentManager.setParentTag(parentTag);
  }

  private setDescriptor(descriptor: ViewBaseDescriptor) {
    this.descriptorWrapper = new ViewDescriptorWrapper(descriptor)
  }

  getHitTestMode() {
    switch (this.descriptorWrapper?.pointerEvents) {
      case "none":
        return HitTestMode.None
      case "box-none":
        return HitTestMode.None
      case "box-only":
        return HitTestMode.Block
      default:
        return HitTestMode.Default
    }
  }

  getBorderStyle(): BorderStyle {
    switch (this.descriptorWrapper?.borderStyle) {
      case "dashed":
        return BorderStyle.Dashed
      case "dotted":
        return BorderStyle.Dotted
      default:
        return BorderStyle.Solid
    }
  }

  getTransform(): undefined | matrix4.Matrix4Transit {
    const descriptorWrapper = this.descriptorWrapper
    if (!descriptorWrapper) {
      return undefined
    }
    const rawTransformationMatrix = descriptorWrapper.rawTransformationMatrix.slice()
    rawTransformationMatrix[12] = vp2px(rawTransformationMatrix[12]);
    rawTransformationMatrix[13] = vp2px(rawTransformationMatrix[13]);
    rawTransformationMatrix[14] = vp2px(rawTransformationMatrix[14]);
    return matrix4.init(rawTransformationMatrix as TransformMatrix)
  }

  build() {
    Text(this.fragment && capitalizeTextIfNecessary(this.fragment?.text, this.fragment?.textTransform))
      .fontColor(convertColorSegmentsToString(this.fragment?.fontColor))
      .fontFamily(this.fragment?.fontFamily)
      .fontWeight(this.fragment?.fontWeight)
      .fontSize(this.fragment?.fontSize)
      .fontStyle(stringToFontStyle(this.fragment?.fontStyle))
      .decoration({
        type: getTextDecorationLine(this.fragment?.textDecorationLine),
        color: convertColorSegmentsToString(this.fragment?.textDecorationColor ?? this.fragment?.fontColor)
      })
      .lineHeight(this.fragment?.lineHeight || (this.fragment?.fontSize ?? 16) * (DEFAULT_LINE_SPACING + 1))
      .backgroundColor(convertColorSegmentsToString(this.fragment?.backgroundColor))
      .letterSpacing(getLetterSpacing(this.fragment?.letterSpacing))
      .textCase(stringToTextTransform(this.fragment?.textTransform))
      .maxLines(getMaxLines(this.descriptor.props.maximumNumberOfLines))
      .textShadow(getTextShadow(this.fragment?.textShadowProps))
      .textOverflow({ overflow: ellipsizeModeToTextOverflow(this.descriptor.props.ellipsizeMode) })
      .textAlign(stringToAlignment(this.descriptor.props.textAlign))
      .align(stringToVerticalAlign(this.descriptor.props.textAlignVertical))
      .padding(this.descriptor.props.padding)
      .copyOption(this.descriptor.props.selectable ? CopyOptions.LocalDevice : CopyOptions.None)
      .enabled(!this.descriptor.props.disabled)

      .width(this.descriptorWrapper?.width)
      .height(this.descriptorWrapper?.height)
      .backgroundColor(this.descriptorWrapper?.backgroundColor)
      .position(this.descriptorWrapper?.positionRelativeToParent)
      .borderWidth(this.descriptorWrapper?.borderWidth)
      .borderColor(this.descriptorWrapper?.borderColor)
      .borderRadius(this.descriptorWrapper?.borderRadius)
      .borderStyle(this.getBorderStyle())
      .opacity(this.descriptorWrapper?.opacity)
      .transform(this.getTransform())
      .clip(this.descriptorWrapper?.isClipping)
      .hitTestBehavior(this.getHitTestMode())
      .shadow(this.descriptorWrapper?.shadow)
      .id(this.tag.toString())
      .accessibilityGroup(this.descriptorWrapper?.accessibilityGroup)
      .accessibilityText(this.descriptorWrapper?.accessibilityText)
      .accessibilityLevel(this.descriptorWrapper?.accessibilityLevel)
      .accessibilityDescription(this.descriptorWrapper?.accessibilityDescription)
  }
}