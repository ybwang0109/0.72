import type resmgr from "@ohos.resourceManager";
import http from '@ohos.net.http';
import util from '@ohos.util';


export interface JSBundleProvider {
  getURL(): string

  getBundle(): Promise<ArrayBuffer>

  getAppKeys(): string[]
}


export class JSBundleProviderError extends Error {
  constructor(private msg: string, private originalError: unknown = undefined) {
    super(msg)
  }
}


export class ResourceJSBundleProvider implements JSBundleProvider {
  constructor(private resourceManager: resmgr.ResourceManager, private path: string = "bundle.harmony.js", private appKeys: string[] = []) {
  }

  getURL() {
    return this.path
  }

  getAppKeys() {
    return this.appKeys
  }

  async getBundle() {
    try {
      const bundleFileContent = await this.resourceManager.getRawFileContent(this.path);
      const bundle = bundleFileContent.buffer;
      return bundle;
    } catch (err) {
      throw new JSBundleProviderError(`Couldn't load JSBundle from ${this.path}`, err)
    }
  }
}


export class MetroJSBundleProvider implements JSBundleProvider {
  constructor(private bundleUrl: string = "http://localhost:8081", private appKeys: string[] = []) {
  }

  getAppKeys() {
    return this.appKeys
  }

  getURL() {
    return this.bundleUrl
  }

  async getBundleSplit() {
    const httpRequest = http.createHttp();
    let content = '';
    try {
      const rsp = await httpRequest.request(
        this.bundleUrl + '/split-pkgs',
        {
          header: {
            'Content-Type': 'text/javascript'
          },
        }
      );
      for (let i = 0; i < (rsp.result as number); i++) {
        const data = await httpRequest.request(
          this.bundleUrl + '/get-pkg',
          {
            header: {
              'Content-Type': 'text/javascript',
              'pkg': i + '',
            },
          }
        );
        content = content + (data.result as string)
      }
      const encoder = new util.TextEncoder();
      const result = encoder.encodeInto(content);
      return result.buffer;
    } catch (err) {
      throw new JSBundleProviderError(`Couldn't load JSBundle from ${this.bundleUrl}`, err)
    } finally {
      httpRequest.destroy();
    }
  }

  async getBundle() {
    const httpRequest = http.createHttp();
    let content = '';
    try {
      const rsp = await httpRequest.request(
        this.bundleUrl + '/split-pkgs',
        {
          header: {
            'Content-Type': 'text/javascript'
          },
        }
      );
      for (let i = 0; i < (rsp.result as number); i++) {
        const data = await httpRequest.request(
          this.bundleUrl + '/get-pkg',
          {
            header: {
              'Content-Type': 'text/javascript',
              'pkg': i + '',
            },
          }
        );
        content = content + (data.result as string)
      }
      const encoder = new util.TextEncoder();
      const result = encoder.encodeInto(content);
      return result.buffer;
    } catch (err) {
      throw new JSBundleProviderError(`Couldn't load JSBundle from ${this.bundleUrl}`, err)
    } finally {
      httpRequest.destroy();
    }
  }

  async getBundleSmall() {
    const httpRequest = http.createHttp();
    try {
      const data = await httpRequest.request(
        this.bundleUrl,
        {
          header: {
            'Content-Type': 'text/javascript'
          },
        }
      );
      const encoder = new util.TextEncoder();
      const result = encoder.encodeInto(data.result as string);
      return result.buffer;
    } catch (err) {
      throw new JSBundleProviderError(`Couldn't load JSBundle from ${this.bundleUrl}`, err)
    } finally {
      httpRequest.destroy();
    }
  }
}

export class AnyJSBundleProvider implements JSBundleProvider {
  private pickedJSBundleProvider: JSBundleProvider | undefined = undefined

  constructor(private jsBundleProviders: JSBundleProvider[]) {
    if (jsBundleProviders.length === 0) {
      throw new JSBundleProviderError("Expected at least 1 JS bundle provider")
    }
  }

  getURL() {
    const jsBundleProvider = this.pickedJSBundleProvider ?? this.jsBundleProviders[0]
    return jsBundleProvider?.getURL() ?? "?"
  }

  getAppKeys() {
    if (!this.pickedJSBundleProvider) {
      return []
    }
    return this.pickedJSBundleProvider.getAppKeys()
  }

  async getBundle() {
    const errors: JSBundleProviderError[] = []
    for (const jsBundleProvider of this.jsBundleProviders) {
      try {
        return await jsBundleProvider.getBundle()
      } catch(err) {
        if (err instanceof JSBundleProviderError) {
          errors.push(err)
        }
      }
    }
    throw new JSBundleProviderError("Any of the jsBundleProviders was able to load the bundle", errors)
  }
}