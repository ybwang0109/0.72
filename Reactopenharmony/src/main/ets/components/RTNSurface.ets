import { ReactRootView } from '../react/ReactRootView'
import hilog from '@ohos.hilog'

@Component
export struct RTNSurface {
  @State started: boolean = false;
  @LocalStorageLink('ReactViewModule') mReactRootView: ReactRootView | null = null; //todo: 修改可以通过设置的SurfaceID获取指定ReactRootView
  private readonly RTNSurface = "RTNSurface"

  aboutToAppear() {
    hilog.info(0x0000, this.RTNSurface, '%{public}s', 'aboutToAppear()');
    this.mReactRootView?.onAboutToAppear();
  }

  aboutToDisappear() {
    this.mReactRootView?.onAboutToDisappear();
  }

  build() {
    Row() {
      Column() {
        Button("Start RN")
          .height(50)
          .margin({top: 16})
          .onClick(() => {
            // rnoh.startReactNative()
          })
	      XComponent({
		    id: "5",
		    type: "node",
		    libraryname: 'react_arkui'
	      })
        .width("100%")
        .height(700)
        .shadow({radius: 16})
        .backgroundColor("white")
        .onAreaChange((oldArea, newArea) => {
          hilog.info(0x0000, this.RTNSurface, '%{public}s', 'onAreaChange()');
          this.mReactRootView?.onAreaChange(oldArea, newArea)
        });
      }
      .height("100%")
      .width('100%')
    }
    .height('100%')
    .backgroundColor("#DDD")
    .alignItems(VerticalAlign.Top)
  }
}