import type { TurboModuleContext } from '../../RNOH/TurboModule';
import { TurboModule } from '../../RNOH/TurboModule';
import {
  RemoteImageDiskCache,
  RemoteImageLoader,
  RemoteImageLoaderError,
  RemoteImageMemoryCache
} from '../../RemoteImageLoader';
import image from '@ohos.multimedia.image';

export class ImageLoaderTurboModule extends TurboModule {
  static NAME = "ImageLoader" as const

  private imageLoader: RemoteImageLoader

  constructor(protected ctx: TurboModuleContext) {
    super(ctx)
    this.imageLoader = new RemoteImageLoader(
      new RemoteImageMemoryCache(128), new RemoteImageDiskCache(128), ctx.uiAbilityContext)
  }

  public getConstants() {
    return {}
  }

  public async getSize(uri: string): Promise<number[]> {
    const imageSource = await this.imageLoader.getImageSource(uri)
    const imageInfo = await imageSource.getImageInfo()
    return [imageInfo.size.width, imageInfo.size.height]
  }

  public getSizeWithHeaders(uri: string, headers: Object): Promise<{
    width: number,
    height: number
  } & Record<string, any>> {
    this.ctx.logger.warn("ImageLoader::getSizeWithHeaders is not supported")
    return Promise.resolve({ width: 0, height: 0 })
  }

  public async prefetchImage(uri: string): Promise<boolean> {
    return this.imageLoader.prefetch(uri);
  }

  public prefetchImageWithMetadata(uri: string, queryRootName: string, rootTag: number): Promise<boolean> {
    this.ctx.logger.warn("ImageLoader::prefetchImageWithMetadata is not supported")
    return Promise.resolve(false)
  }

  public queryCache(uris: Array<string>): Promise<Object> {
    const cachedUriEntries = uris.map(uri =>
      [uri, this.imageLoader.queryCache(uri)]
    ).filter(([_uri, value]) => value !== undefined);
    const cachedUriMap = Object.fromEntries(cachedUriEntries)
    return Promise.resolve(cachedUriMap)
  }

  public getCachedImage(uri: string): string | undefined {
    return this.imageLoader.getImageFromCache(uri)
  }

  public async getImageSource(uri: string): Promise<image.ImageSource> {
    try {
      const imageSource = await this.imageLoader.getImageSource(uri);
      return imageSource
    }
    catch (e) {
      if (!(e instanceof RemoteImageLoaderError) && e instanceof Object && e.message) {
        throw new RemoteImageLoaderError(`Failed to load the image: ${e.message}`)
      }
      throw new RemoteImageLoaderError(`Failed to load the image.`)

    }
  }
}