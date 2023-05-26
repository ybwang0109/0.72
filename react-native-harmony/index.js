module.exports = {
  get Animated() {
    return require('react-native/Libraries/Animated/Animated').default
  },
  get Easing() {
    return require('react-native/Libraries/Animated/Easing').default
  },
  get AppRegistry() {
    return require('react-native/Libraries/ReactNative/AppRegistry')
  },
  get FlatList() {
    return require('react-native/Libraries/Lists/FlatList')
  },
  get Image() {
    return require('react-native/Libraries/Image/Image')
  },
  get I18nManager() {
    return require('react-native/Libraries/ReactNative/I18nManager')
  },
  get NativeEventEmitter() {
    return require('react-native/Libraries/EventEmitter/NativeEventEmitter').default;
  },
  get NativeModules() {
    return require('react-native/Libraries/BatchedBridge/NativeModules')
  },
  get Platform() {
    return require('./Libraries/Utilities/Platform')
  },
  get PixelRatio() {
    return require('react-native/Libraries/Utilities/PixelRatio')
  },
  get ScrollView() {
    return require('react-native/Libraries/Components/ScrollView/ScrollView')
  },
  get StyleSheet() {
    return require('react-native/Libraries/StyleSheet/StyleSheet')
  },
  get Text() {
    return require('react-native/Libraries/Text/Text')
  },
  get TextInput() {
    return require('./Libraries/Components/TextInput/TextInput.harmony')
  },
  get TurboModuleRegistry() {
    return require('react-native/Libraries/TurboModule/TurboModuleRegistry')
  },
  get UIManager() {
    return require('react-native/Libraries/ReactNative/UIManager')
  },
  get useAnimatedValue() {
    return require('react-native/Libraries/Animated/useAnimatedValue').default
  },
  get View() {
    return require('react-native/Libraries/Components/View/View')
  },
  get PanResponder() {
    return require('react-native/Libraries/Interaction/PanResponder')
  },
  get processColor() {
    return require('react-native/Libraries/StyleSheet/processColor')
  },
  get SectionList() {
    return require('react-native/Libraries/Lists/SectionList').default
  },
}
