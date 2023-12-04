import { TurboModule, TurboModuleContext } from "../../RNOH/TurboModule";

export class FileReaderTurboModule extends TurboModule {
  public static readonly NAME = 'FileReaderModule';

  constructor(protected ctx: TurboModuleContext) {
    super(ctx);
  }

  readAsDataURL(data: Object): Promise<string> {
    console.log(`FileReaderTurboModule call readAsDataURL`)
    return null;
  }

  readAsText(data: Object, encoding: string): Promise<string> {
    console.log(`FileReaderTurboModule call readAsText`)
    return null;
  }
}