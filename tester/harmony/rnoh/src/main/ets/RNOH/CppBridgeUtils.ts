import matrix4 from '@ohos.matrix4'
import { ColorSegments, ColorValue } from './DescriptorBase'

// gets rid of DevEco warnings
declare function vp2px(vp: number): number;

export function convertColorSegmentsToString(colorSegments?: ColorSegments) {
  if (!colorSegments) return undefined
  const [r, g, b, a] = colorSegments
  return `rgba(${Math.round(r * 255)}, ${Math.round(g * 255)}, ${Math.round(
    b * 255
  )}, ${a})`
}

export function getTintColorMatrix(colorSegments?: ColorSegments) {
  if (!colorSegments || colorSegments.every((element) => element === 0)) {
    return [
      1, 0, 0, 0, 0,
      0, 1, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 1, 0,
    ]
  }
  const [r, g, b, a] = colorSegments
  return [
    0, 0, 0, r, 0,
    0, 0, 0, g, 0,
    0, 0, 0, b, 0,
    0, 0, 0, 1, 0,
  ]
}

export function convertColorValueToRGBA(colorValue: ColorValue | undefined, defaultColor: string = "rgba(0,0,0,0.0)") {
  if (colorValue === undefined) return defaultColor;
  const rgba = {
    a: ((colorValue >> 24) & 0xff) / 255,
    r: (colorValue >> 16) & 0xff,
    g: (colorValue >> 8) & 0xff,
    b: ((colorValue >> 0) & 0xff),
  }
  return `rgba(${rgba.r}, ${rgba.g}, ${rgba.b}, ${rgba.a})`
}
export function convertColorValueToHex(colorValue: ColorValue | undefined, defaultColor: string = "#00000000") {
  if (colorValue === undefined) return defaultColor;
  const toHex = (num, padding) => num.toString(16).padStart(padding, '0');
  const argb = {
    a: (colorValue >> 24) & 0xff,
    r: (colorValue >> 16) & 0xff,
    g: (colorValue >> 8) & 0xff,
    b: ((colorValue >> 0) & 0xff),
  }
  return `#${toHex(argb.a, 2)}${toHex(argb.r, 2)}${toHex(argb.g, 2)}${toHex(argb.b, 2)}`;
}

export function convertColorValueToColorSegments(colorValue: ColorValue | undefined): ColorSegments | undefined {
  if (colorValue === undefined) return undefined
  const rgba = {
    a: ((colorValue >> 24) & 0xff) / 255,
    r: ((colorValue >> 16) & 0xff) / 255,
    g: ((colorValue >> 8) & 0xff) / 255,
    b: ((colorValue >> 0) & 0xff) / 255,
  }
  return [rgba.r, rgba.g, rgba.b, rgba.a]
}

export type TransformMatrix = [
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number
];

export function convertMatrixArrayToMatrix4(transform: TransformMatrix) {
  if (transform.length < 16)
    return matrix4.identity();
  transform = transform.slice() as TransformMatrix;
  transform[12] = vp2px(transform[12]);
  transform[13] = vp2px(transform[13]);
  transform[14] = vp2px(transform[14]);
  return matrix4.init(transform);
}
