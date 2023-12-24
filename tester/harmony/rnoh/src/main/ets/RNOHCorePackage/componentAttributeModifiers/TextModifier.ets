import {
  BorderMetrics,
  convertColorSegmentsToString,
  convertColorValueToColorSegments,
  Descriptor,
  getTransformedVector,
  LayoutDirectionRN,
  OverflowMode,
  resolveBorderMetrics,
  RNOHContext,
  DEFAULT_LINE_SPACING,
  TransformMatrix
} from '../../RNOH';
import { ViewDescriptorWrapper } from '../components/RNViewBase/ViewDescriptorWrapper';
import { TextDescriptor, AttributedFragment, EllipsizeMode} from '../components/RNText/types';
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
  capitalizeTextIfNecessary
} from '../components/RNText/conversions'
import matrix4 from '@ohos.matrix4';

export class TextModifier implements AttributeModifier<TextAttribute> {
  private constructor() {}
  private static instance: TextModifier;
  protected descriptor: TextDescriptor = {} as TextDescriptor;
  protected descriptorWrapper: ViewDescriptorWrapper | undefined = undefined
  protected fragment: AttributedFragment | undefined = undefined;
  protected tag: number = 0

  public static getInstance(): TextModifier {
    if (!TextModifier.instance) {
      TextModifier.instance = new TextModifier();
    }
    return TextModifier.instance;
  }

  setDescriptor(descriptor: TextDescriptor, descriptorWrapper: ViewDescriptorWrapper | undefined = undefined, fragment: AttributedFragment | undefined, tag: number): TextModifier {
    this.descriptor = descriptor;
    this.descriptorWrapper = descriptorWrapper;
    this.fragment = fragment;
    this.tag = tag;
    return TextModifier.instance;
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

  applyNormalAttribute(instance: TextAttribute): void {
    instance.width(this.descriptorWrapper?.width);
    instance.height(this.descriptorWrapper?.height);
    instance.position(this.descriptorWrapper?.positionRelativeToParent);
    instance.id(this.tag.toString())

    if (this.descriptorWrapper?.backgroundColor !== '#00000000') {
      instance.backgroundColor(this.descriptorWrapper?.backgroundColor)
    }
    if (JSON.stringify(this.descriptorWrapper?.borderWidth) !== '{}') {
      instance.borderWidth(this.descriptorWrapper?.borderWidth)
    }
    if (JSON.stringify(this.descriptorWrapper?.borderColor) !== '{"top":"#00000000","left":"#00000000","right":"#00000000","bottom":"#00000000"}') {
      instance.borderColor(this.descriptorWrapper?.borderColor)
    }
    if (JSON.stringify(this.descriptorWrapper?.borderRadius) !== '{}') {
      instance.borderRadius(this.descriptorWrapper?.borderRadius)
    }
    if (this.descriptorWrapper?.borderStyle === 'dashed' || this.descriptorWrapper?.borderStyle === 'dotted') {
      instance.borderStyle(this.getBorderStyle())
    }
    if (this.descriptorWrapper?.opacity !== 1) {
      instance.opacity(this.descriptorWrapper?.opacity)
    }
    if (this.descriptorWrapper?.transformStringify !== '[1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]') {
      instance.transform(this.getTransform())
    }
    if (this.descriptorWrapper?.isClipping) {
      instance.clip(this.descriptorWrapper?.isClipping)
    }
    let hitTestBehavior: HitTestMode = this.getHitTestMode();
    if (hitTestBehavior !== HitTestMode.Default) {
      instance.hitTestBehavior(hitTestBehavior)
    }
    if (this.descriptorWrapper?.shadow) {
      instance.shadow(this.descriptorWrapper?.shadow)
    }
    if (JSON.stringify(this.descriptorWrapper?.accessibilityGroup) !== 'auto') {
      instance.accessibilityGroup(this.descriptorWrapper?.accessibilityGroup)
    }
    if (this.descriptorWrapper?.accessibilityText) {
      instance.accessibilityText(this.descriptorWrapper?.accessibilityText)
    }
    if (this.descriptorWrapper?.accessibilityLevel) {
      instance.accessibilityLevel(this.descriptorWrapper?.accessibilityLevel)
    }
    if (this.descriptorWrapper?.accessibilityDescription) {
      instance.accessibilityDescription(this.descriptorWrapper?.accessibilityDescription)
    }

    if (JSON.stringify(this.fragment?.fontColor) !== '0,0,0,1') {
      instance.fontColor(convertColorSegmentsToString(this.fragment?.fontColor))
    }
    if (this.fragment?.fontFamily) {
      instance.fontFamily(this.fragment?.fontFamily)
    }
    if (this.fragment?.fontWeight !== FontWeight.Normal) {
      instance.fontWeight(this.fragment?.fontWeight)
    }
    if (this.fragment?.fontSize) {
      instance.fontSize(this.fragment?.fontSize)
    }
    if (stringToFontStyle(this.fragment?.fontStyle) !== FontStyle.Normal) {
      instance.fontStyle(stringToFontStyle(this.fragment?.fontStyle))
    }
    if (this.fragment?.textDecorationLine) {
      instance.decoration({
        type: getTextDecorationLine(this.fragment?.textDecorationLine),
        color: convertColorSegmentsToString(this.fragment?.textDecorationColor ?? this.fragment?.fontColor)
      })
    }
    if (JSON.stringify(this.fragment?.backgroundColor) !== '0,0,0,0') {
      instance.backgroundColor(convertColorSegmentsToString(this.fragment?.backgroundColor))
    }
    if (this.fragment?.letterSpacing) {
      instance.letterSpacing(getLetterSpacing(this.fragment?.letterSpacing))
    }
    if (stringToTextTransform(this.fragment?.textTransform) !== TextCase.Normal) {
      instance.textCase(stringToTextTransform(this.fragment?.textTransform))
    }
    if (this.descriptor.props.maximumNumberOfLines) {
      instance.maxLines(getMaxLines(this.descriptor.props.maximumNumberOfLines))
    }
    if (this.fragment?.textShadowProps) {
      instance.textShadow(getTextShadow(this.fragment?.textShadowProps))
    }
    if (ellipsizeModeToTextOverflow(this.descriptor.props.ellipsizeMode as EllipsizeMode) !== TextOverflow.Clip) {
      instance.textOverflow({ overflow: ellipsizeModeToTextOverflow(this.descriptor.props.ellipsizeMode as EllipsizeMode) })
    }
    if (stringToAlignment(this.descriptor.props.textAlign) !== TextAlign.Start) {
      instance.textAlign(stringToAlignment(this.descriptor.props.textAlign))
    }
    if (stringToVerticalAlign(this.descriptor.props.textAlignVertical) !== Alignment.Center) {
      instance.align(stringToVerticalAlign(this.descriptor.props.textAlignVertical))
    }
    if (this.descriptor.props.padding) {
      instance.padding(this.descriptor.props.padding)
    }
    if (this.descriptor.props.selectable) {
      instance.copyOption(CopyOptions.LocalDevice)
    }
    instance.lineHeight(this.fragment?.lineHeight || (this.fragment?.fontSize ?? 16) * (DEFAULT_LINE_SPACING + 1))
    instance.enabled(!this.descriptor.props.disabled)
  }
}