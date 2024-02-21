import { RTNSurface } from '@ohos/react-openharmony';

let storage = LocalStorage.getShared()

@Entry(storage)
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    Row() {
      Column() {
        RTNSurface()
          .width('100%')
          .height('100%')
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
  }
}
