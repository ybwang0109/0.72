import { ColorSegments, Descriptor, Tag } from '../../../RNOH/DescriptorBase'
import { OHOSMeasurerTextFragmentExtraData } from '../../../RNOH/TextLayoutManager'
import { ViewBaseProps } from '../RNViewBase/types'

export type AttributedFragment = {
  text?: string
  fontColor?: ColorSegments
  fontWeight?: number
  fontSize?: number
  fontStyle?: string
  textDecorationLine?: number
  textDecorationColor?: ColorSegments
  textTransform?: string
  lineHeight?: number
  backgroundColor?: ColorSegments
  letterSpacing?: number
  textShadowProps?: TextShadowProps
  parentShadowView?: {
    tag: Tag,
    layoutMetrics: {
      frame: {
        size: {
          width: number,
          height: number
        }
      }
    }
  }
}

export type TextFragmentExtraData = OHOSMeasurerTextFragmentExtraData & {
  fontColor?: string
  backgroundColor?: string
  fontStyle?: string
  textDecorationColor?: ColorSegments,
  textDecorationLine?: number,
  textTransform?: string,
  textShadowProps?: TextShadowProps
}

export type TextDescriptor = Descriptor<"Paragraph", TextProps>

export type TextShadowProps = {
  textShadowColor?: ColorSegments,
  textShadowOffset?: {
    width: number,
    height: number
  },
  textShadowRadius?: number,
}

export type TextProps = ViewBaseProps & {
  textAlign?: string
  fragments: AttributedFragment[]
  padding?: PaddingProps
  maximumNumberOfLines?: number
  textAlignVertical?: string
  selectable?: boolean
  disabled?: boolean
  ellipsizeMode?: EllipsizeMode
}

type PaddingProps = {
  top: number,
  right: number,
  bottom: number,
  left: number
}

export enum EllipsizeMode {
  Clip,
  Head,
  Tail,
  Middle,
}