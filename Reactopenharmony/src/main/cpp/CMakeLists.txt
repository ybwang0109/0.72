cmake_minimum_required(VERSION 3.4.1)
project(rnopenharmony)

set(RNOH_CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(NATIVERENDER_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(third_party_dir "${CMAKE_CURRENT_SOURCE_DIR}/third-party")
set(patches_dir "${CMAKE_CURRENT_SOURCE_DIR}/patches")

add_compile_options("-Wno-unused-command-line-argument")

include_directories(${NATIVERENDER_ROOT_PATH}
					${NATIVERENDER_ROOT_PATH}/include)

###################################### -------- build library -------- ######################################
#
## FMT
#add_library(fmt_target SHARED IMPORTED)
#set_property(TARGET fmt_target PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libfmt_target.a")
#
## DOUBLE CONVERSION
#set(double_conversion_include_dir "${third_party_dir}/include/double-conversion")
#add_library(double_conversion_target SHARED IMPORTED)
#set_property(TARGET double_conversion_target PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libdouble_conversion_target.a")
#
## GLOG
#set(glog_include_dir "${third_party_dir}/include/glog/src")
#add_library(glog_target SHARED IMPORTED)
#set_property(TARGET glog_target PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libglog_target.a")
#
## BOOST
#set(boost_libs_dir "${third_party_dir}/include/boost/libs")
#file(GLOB boost_include_dirs "${boost_libs_dir}/*/include")
#add_library(Boost::context SHARED IMPORTED)
#set_property(TARGET Boost::context PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libboost_context.a")
#
## LIBEVENT
#add_library(libevent SHARED IMPORTED)
#set_property(TARGET libevent PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/liblibevent.a")
#
## FOLLY
#set(folly_include_dir "${third_party_dir}/include/folly")
#add_library(folly_target SHARED IMPORTED)
#set_property(TARGET folly_target PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libfolly_target.a")
#
## FOLLY FUTURES
#add_library(folly_futures SHARED IMPORTED)
#set_property(TARGET folly_futures PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libfolly_futures.a")
#
## HERMES
#add_library(hermes-engine::libhermes SHARED IMPORTED)
#set(hermes_include_dirs
#    "${third_party_dir}/include/hermes/API"
#    "${third_party_dir}/include/hermes/public"
#)
#set_property(TARGET hermes-engine::libhermes PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libhermes.so")
#
## -------- REACT COMMON --------
#set(REACT_COMMON_DIR "${third_party_dir}/rn/ReactCommon")
#set(REACT_COMMON_PATCH_DIR "${patches_dir}/react_native_core")
#
#add_library(hermes_executor_common SHARED IMPORTED)
#set_property(TARGET hermes_executor_common PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libhermes_executor_common.a")
#
#add_library(hermes_inspector SHARED IMPORTED)
#set_property(TARGET hermes_inspector PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libhermes_inspector.a")
#
#add_library(jsi SHARED IMPORTED)
#set_property(TARGET jsi PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libjsi.so")
#
#add_library(jsinspector SHARED IMPORTED)
#set_property(TARGET jsinspector PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libjsinspector.so")
#
#add_library(jsireact SHARED IMPORTED)
#set_property(TARGET jsireact PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libjsireact.a")
#
#add_library(logger SHARED IMPORTED)
#set_property(TARGET logger PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/liblogger.so")
#
#add_library(runtimeexecutor SHARED IMPORTED)
#set_property(TARGET runtimeexecutor PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libruntimeexecutor.so")
#
#add_library(reactperflogger SHARED IMPORTED)
#set_property(TARGET reactperflogger PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreactperflogger.a")
#
#add_library(react_config SHARED IMPORTED)
#set_property(TARGET react_config PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_config.so")
#
#add_library(react_debug SHARED IMPORTED)
#set_property(TARGET react_debug PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_debug.so")
#
#add_library(react_nativemodule_core SHARED IMPORTED)
#set_property(TARGET react_nativemodule_core PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_nativemodule_core.so")
#
#add_library(reactnative SHARED IMPORTED)
#set_property(TARGET reactnative PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreactnative.a")
#
#add_library(react_render_scheduler SHARED IMPORTED)
#set_property(TARGET react_render_scheduler PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_scheduler.so")
#
#add_library(react_renderer_componentregistry SHARED IMPORTED)
#set_property(TARGET react_renderer_componentregistry PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_componentregistry.so")
#
#add_library(react_render_animations SHARED IMPORTED)
#set_property(TARGET react_render_animations PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_animations.so")
#
#add_library(react_render_attributedstring SHARED IMPORTED)
#set_property(TARGET react_render_attributedstring PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_attributedstring.so")
#
#add_library(react_render_core SHARED IMPORTED)
#set_property(TARGET react_render_core PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_core.so")
#
#add_library(react_render_debug SHARED IMPORTED)
#set_property(TARGET react_render_debug PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_debug.so")
#
#add_library(react_render_graphics SHARED IMPORTED)
#set_property(TARGET react_render_graphics PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_graphics.so")
#
#add_library(react_render_imagemanager SHARED IMPORTED)
#set_property(TARGET react_render_imagemanager PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_imagemanager.so")
#
#add_library(react_render_leakchecker SHARED IMPORTED)
#set_property(TARGET react_render_leakchecker PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_leakchecker.so")
#
#add_library(react_render_mapbuffer SHARED IMPORTED)
#set_property(TARGET react_render_mapbuffer PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_mapbuffer.so")
#
#add_library(react_render_mountin SHARED IMPORTED)
#set_property(TARGET react_render_mountin PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_mounting.so")
#
#add_library(react_render_runtimescheduler SHARED IMPORTED)
#set_property(TARGET react_render_runtimescheduler PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_runtimescheduler.so")
#
#add_library(react_render_telemetry SHARED IMPORTED)
#set_property(TARGET react_render_telemetry PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_telemetry.so")
#
#add_library(react_render_templateprocessor SHARED IMPORTED)
#set_property(TARGET react_render_templateprocessor PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_templateprocessor.so")
#
#add_library(react_render_textlayoutmanager SHARED IMPORTED)
#set_property(TARGET react_render_textlayoutmanager PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_textlayoutmanager.so")
#
#add_library(react_render_uimanager SHARED IMPORTED)
#set_property(TARGET react_render_uimanager PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_render_uimanager.so")
#
#add_library(rrc_root SHARED IMPORTED)
#set_property(TARGET rrc_root PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_root.so")
#
#add_library(rrc_view SHARED IMPORTED)
#set_property(TARGET rrc_view PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_view.so")
#
#add_library(rrc_image SHARED IMPORTED)
#set_property(TARGET rrc_image PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_image.so")
#
#add_library(rrc_text SHARED IMPORTED)
#set_property(TARGET rrc_text PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_text.so")
#
#add_library(rrc_textinput SHARED IMPORTED)
#set_property(TARGET rrc_textinput PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_textinput.so")
#
#add_library(rrc_scrollview SHARED IMPORTED)
#set_property(TARGET rrc_scrollview PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_scrollview.so")
#
#add_library(rrc_modal SHARED IMPORTED)
#set_property(TARGET rrc_modal PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/librrc_modal.a")
#
#add_library(react_codegen_rncore SHARED IMPORTED)
#set_property(TARGET react_codegen_rncore PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_codegen_rncore.a")
#
#add_library(react_bridging SHARED IMPORTED)
#set_property(TARGET react_bridging PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_bridging.a")
#
#add_library(react_utils SHARED IMPORTED)
#set_property(TARGET react_utils PROPERTY
#                IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libreact_utils.so")
#
#set(folly_compile_options
#    -DFOLLY_NO_CONFIG=1
#    -DFOLLY_MOBILE=1
#    -DFOLLY_USE_LIBCPP=1
#    -DFOLLY_HAVE_RECVMMSG=1
#    -DFOLLY_HAVE_PTHREAD=1
#    -Wno-comma
#    -Wno-shorten-64-to-32
#    -Wno-documentation
#    -faligned-new
#)
#
#add_subdirectory(third-party/aki)
#
#add_library(react_arkui SHARED
#    "${RNOH_CPP_DIR}/react_arkui_napi.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/native_instance/NativeCatalystInstance.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/fabric/RNOHFabricUIManager.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/MessageQueueThread.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/MutationsToNapiConverter.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/LogSink.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/NativeLogger.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/ArkJS.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/MountingManager.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/ShadowViewRegistry.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TurboModuleProvider.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TurboModuleFactory.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/ArkTSTurboModule.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/JsiConversions.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/Package.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/UIManagerModule.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TextMeasurer.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TaskExecutor/TaskExecutor.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TaskExecutor/NapiTaskRunner.cpp"
#    "${RNOH_CPP_DIR}/react_arkui/TaskExecutor/ThreadTaskRunner.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/AccessibilityInfoTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/AlertManagerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/AppearanceTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/AppStateTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/AppearanceTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/BlobTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/DeviceInfoTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/DeviceEventManagerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/DevSplitBundleLoaderTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/ExceptionsManagerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/FileReaderTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/FrameRateLoggerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/I18nTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/ImageLoaderTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/ImageStoreTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/LinkingManagerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/NetworkingTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/PlatformConstantsTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/RNCLogTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/SourceCodeTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/StatusBarTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/TimingTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/WebSocketTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/SafeAreaTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/NativeAnimatedTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/AnimatedNodesManager.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Nodes/AnimatedNode.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Nodes/TransformAnimatedNode.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Nodes/InterpolationAnimatedNode.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Nodes/DiffClampAnimatedNode.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Nodes/TrackingAnimatedNode.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Drivers/AnimationDriver.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Drivers/FrameBasedAnimationDriver.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Drivers/SpringAnimationDriver.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Drivers/DecayAnimationDriver.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/Animated/Drivers/EventAnimationDriver.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/TurboModules/I18nManagerTurboModule.cpp"
#    "${RNOH_CPP_DIR}/RNOHCorePackage/EventEmitRequestHandlers/TouchEventEmitRequestHandler.cpp"
#)
#target_include_directories(react_arkui PUBLIC
#    "${RNOH_CPP_DIR}"
#    "${REACT_COMMON_DIR}"
#    "${REACT_COMMON_PATCH_DIR}"
#    "${REACT_COMMON_PATCH_DIR}/react/renderer/textlayoutmanager/platform/harmony"
#    "${REACT_COMMON_DIR}/jsiexecutor"
#    "${REACT_COMMON_DIR}/jsi"
#    "${REACT_COMMON_DIR}/runtimeexecutor"
#    "${REACT_COMMON_DIR}/callinvoker"
#    "${REACT_COMMON_DIR}/yoga"
#    "${REACT_COMMON_DIR}/react/renderer/graphics/platform/cxx"
#    "${REACT_COMMON_DIR}/react/nativemodule/core"
#    "${fmt_include_dir}"
#    "${double_conversion_include_dir}"
#    "${glog_include_dir}"
#    "${boost_include_dirs}"
#    "${folly_include_dir}"
#    "${hermes_include_dirs}"
#    "${third_party_dir}/aki/include"
#    "${RNOH_APP_DIR}"
#)
#target_link_libraries(react_arkui PUBLIC
#    libace_napi.z.so
#    libhilog_ndk.z.so
#    libnative_vsync.so
#    libnative_drawing.so
#    uv
#    Boost::context
#    reactnative
#    react_render_scheduler
#    hermes_executor_common
#    rrc_image
#    rrc_text
#    rrc_textinput
#    rrc_scrollview
#    rrc_modal
#    jsi
#    jsinspector
#    logger
#    react_bridging
#    react_config
#    react_codegen_rncore
#    react_debug
#    react_nativemodule_core
#    react_render_animations
#    react_render_attributedstring
#    react_render_core
#    react_render_debug
#    react_render_graphics
#    react_render_imagemanager
#    react_render_leakchecker
#    react_render_mapbuffer
#    react_render_mountin
#    react_render_runtimescheduler
#    react_render_telemetry
#    react_render_templateprocessor
#    react_render_textlayoutmanager
#    react_render_uimanager
#    react_renderer_componentregistry
#    react_utils
#    rrc_root
#    rrc_view
#    runtimeexecutor
#    reactperflogger
#    hermes_inspector
#    jsireact
#    hermes-engine::libhermes
#    folly_target
#    folly_futures
#    libevent
#    fmt_target
#    glog_target
#    double_conversion_target
#    aki_jsbind
#)
#target_compile_options(react_arkui PUBLIC ${folly_compile_options}  -DRAW_PROPS_ENABLED -std=c++17)
#
##reactopenharmony
#add_library(reactopenharmony SHARED
# "hello.cpp"
#)
#target_link_libraries(reactopenharmony PUBLIC
#  libace_napi.z.so
#)


###################################### -------- build source -------- ######################################


# FMT
set(fmt_include_dir "${third_party_dir}/fmt/include")
set(fmt_src_dir "${third_party_dir}/fmt/src")
add_library(fmt_target)
target_include_directories(fmt_target PRIVATE
	"${fmt_include_dir}"
)
target_sources(fmt_target PRIVATE
	"${fmt_src_dir}/format.cc"
	"${fmt_src_dir}/os.cc"
)

# DOUBLE CONVERSION
set(double_conversion_include_dir "${third_party_dir}/double-conversion")
set(double_conversion_src_dir "${third_party_dir}/double-conversion/double-conversion")
add_library(double_conversion_target)
target_include_directories(double_conversion_target PRIVATE
	"${double_conversion_include_dir}"
)
target_sources(double_conversion_target PRIVATE
	"${double_conversion_src_dir}/bignum-dtoa.cc"
	"${double_conversion_src_dir}/bignum.cc"
	"${double_conversion_src_dir}/cached-powers.cc"
	"${double_conversion_src_dir}/diy-fp.cc"
	"${double_conversion_src_dir}/double-conversion.cc"
	"${double_conversion_src_dir}/fast-dtoa.cc"
	"${double_conversion_src_dir}/fixed-dtoa.cc"
	"${double_conversion_src_dir}/strtod.cc"
)

# GLOG
set(glog_include_dir "${third_party_dir}/glog/src")
set(glog_src_dir "${third_party_dir}/glog/src")
add_library(glog_target)
target_include_directories(glog_target PUBLIC
    "${glog_include_dir}"
	"${glog_include_dir}/base"
)
target_sources(glog_target PRIVATE
	"${glog_src_dir}/demangle.cc"
	"${glog_src_dir}/logging.cc"
	"${glog_src_dir}/raw_logging.cc"
	"${glog_src_dir}/signalhandler.cc"
	"${glog_src_dir}/symbolize.cc"
	"${glog_src_dir}/utilities.cc"
	"${glog_src_dir}/vlog_is_on.cc"
)
target_compile_options(glog_target PRIVATE
	-Wno-shorten-64-to-32
	-Wno-header-hygiene
	-Wno-deprecated-declarations
	-fdeclspec
)

# BOOST
#set(boost_libs_dir "${third_party_dir}/boost/libs")
#file(GLOB boost_include_dirs "${boost_libs_dir}/*/include")
#set(boost_libs_dir "${third_party_dir}/include/boost/libs")
#file(GLOB boost_include_dirs "${boost_libs_dir}/*/include")
#add_library(Boost::context SHARED IMPORTED)
#set_property(TARGET Boost::context PROPERTY
				IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libboost_context.a")


# BOOST
set(boost_libs_dir "${third_party_dir}/boost/libs")
file(GLOB boost_include_dirs "${boost_libs_dir}/*/include")
set(BOOST_ENABLE_CMAKE On)
add_subdirectory("${boost_libs_dir}/core")
add_subdirectory("${boost_libs_dir}/config")
add_subdirectory("${boost_libs_dir}/assert")
add_subdirectory("${boost_libs_dir}/static_assert")
add_subdirectory("${boost_libs_dir}/type_traits")
add_subdirectory("${boost_libs_dir}/throw_exception")
add_subdirectory("${boost_libs_dir}/move")
add_subdirectory("${boost_libs_dir}/predef")
add_subdirectory("${boost_libs_dir}/pool")
add_subdirectory("${boost_libs_dir}/mp11")
add_subdirectory("${boost_libs_dir}/smart_ptr")
add_subdirectory("${boost_libs_dir}/winapi")
add_subdirectory("${boost_libs_dir}/integer")
add_subdirectory("${boost_libs_dir}/context")

# LIBEVENT
add_library(libevent)
set(libevent_src_dir "${third_party_dir}/libevent")
set(libevent_include_dirs
	"${patches_dir}/libevent/${OHOS_ARCH}"
	"${third_party_dir}/libevent/include"
	"${third_party_dir}/libevent/compat"
)
target_include_directories(libevent PUBLIC
	${libevent_include_dirs}
)
target_sources(libevent PRIVATE
	"${libevent_src_dir}/event.c"
	"${libevent_src_dir}/buffer.c"
	"${libevent_src_dir}/bufferevent.c"
	"${libevent_src_dir}/bufferevent_filter.c"
	"${libevent_src_dir}/bufferevent_pair.c"
	"${libevent_src_dir}/bufferevent_ratelim.c"
	"${libevent_src_dir}/bufferevent_sock.c"
	"${libevent_src_dir}/epoll.c"
	"${libevent_src_dir}/evmap.c"
	"${libevent_src_dir}/evthread.c"
	"${libevent_src_dir}/evthread_pthread.c"
	"${libevent_src_dir}/evutil.c"
	"${libevent_src_dir}/evutil_rand.c"
	"${libevent_src_dir}/evutil_time.c"
	"${libevent_src_dir}/listener.c"
	"${libevent_src_dir}/log.c"
	"${libevent_src_dir}/poll.c"
	"${libevent_src_dir}/signal.c"
	"${libevent_src_dir}/strlcpy.c"
	"${libevent_src_dir}/select.c"
)


# FOLLY
set(folly_include_dir "${third_party_dir}/folly")
set(folly_src_dir "${third_party_dir}/folly/folly")
add_library(folly_target)
target_include_directories(folly_target PUBLIC
	"${folly_include_dir}"
	"${boost_include_dirs}"
	"${double_conversion_include_dir}"
	"${glog_include_dir}"
	"${fmt_include_dir}"
)
set(folly_compile_options
	-DFOLLY_NO_CONFIG=1
	-DFOLLY_MOBILE=1
	-DFOLLY_USE_LIBCPP=1
	-DFOLLY_HAVE_RECVMMSG=1
	-DFOLLY_HAVE_PTHREAD=1
	-Wno-comma
	-Wno-shorten-64-to-32
	-Wno-documentation
	-faligned-new
)
target_compile_options(folly_target PUBLIC ${folly_compile_options})
target_sources(folly_target PRIVATE
	"${folly_src_dir}/SharedMutex.cpp"
	"${folly_src_dir}/concurrency/CacheLocality.cpp"
	"${folly_src_dir}/detail/Futex.cpp"
	"${folly_src_dir}/portability/Malloc.cpp"
	"${folly_src_dir}/synchronization/ParkingLot.cpp"
	"${folly_src_dir}/system/ThreadId.cpp"
	"${folly_src_dir}/lang/SafeAssert.cpp"
	"${folly_src_dir}/lang/ToAscii.cpp"
	"${folly_src_dir}/dynamic.cpp"
	"${folly_src_dir}/hash/SpookyHashV2.cpp"
	"${folly_src_dir}/json_pointer.cpp"
	"${folly_src_dir}/Conv.cpp"
	"${folly_src_dir}/Format.cpp"
	"${folly_src_dir}/memory/detail/MallocImpl.cpp"
	"${folly_src_dir}/json.cpp"
	"${folly_src_dir}/Unicode.cpp"
	"${folly_src_dir}/lang/Assume.cpp"
	"${folly_src_dir}/ScopeGuard.cpp"
)
target_link_libraries(folly_target PUBLIC
	fmt_target
	glog_target
	double_conversion_target
)

# FOLLY FUTURES
add_library(folly_futures)
target_include_directories(folly_futures PUBLIC
    "${folly_include_dir}"
    "${boost_include_dirs}"
    "${double_conversion_include_dir}"
    "${glog_include_dir}"
    "${fmt_include_dir}"
    "${libevent_include_dirs}"
)
target_compile_options(folly_futures PRIVATE
    ${folly_compile_options}
    "-Wno-nullability-completeness"
    "-std=c++17"
)
target_sources(folly_futures PRIVATE
    "${patches_dir}/folly/Demangle.cpp"
    "${folly_src_dir}/ExceptionString.cpp"
    "${folly_src_dir}/ExceptionWrapper.cpp"
    "${folly_src_dir}/Executor.cpp"
    "${folly_src_dir}/FileUtil.cpp"
    "${folly_src_dir}/ScopeGuard.cpp"
    "${folly_src_dir}/String.cpp"
    "${folly_src_dir}/Singleton.cpp"
    "${folly_src_dir}/Try.cpp"
    # "${folly_src_dir}/concurrency/CacheLocality.cpp"
    "${folly_src_dir}/concurrency/DeadlockDetector.cpp"
    "${folly_src_dir}/concurrency/QueueObserver.cpp"
    "${folly_src_dir}/detail/AsyncTrace.cpp"
    "${folly_src_dir}/detail/AtFork.cpp"
    # "${folly_src_dir}/detail/Futex.cpp"
    "${folly_src_dir}/detail/MemoryIdler.cpp"
    "${folly_src_dir}/detail/SingletonStackTrace.cpp"
    "${folly_src_dir}/detail/StaticSingletonManager.cpp"
    "${folly_src_dir}/detail/ThreadLocalDetail.cpp"
    "${folly_src_dir}/detail/UniqueInstance.cpp"
    "${folly_src_dir}/executors/CPUThreadPoolExecutor.cpp"
    "${folly_src_dir}/executors/Codel.cpp"
    "${folly_src_dir}/executors/EDFThreadPoolExecutor.cpp"
    "${folly_src_dir}/executors/ExecutorWithPriority.cpp"
    "${folly_src_dir}/executors/GlobalExecutor.cpp"
    "${folly_src_dir}/executors/GlobalThreadPoolList.cpp"
    "${folly_src_dir}/executors/IOThreadPoolDeadlockDetectorObserver.cpp"
    "${folly_src_dir}/executors/IOThreadPoolExecutor.cpp"
    "${folly_src_dir}/executors/InlineExecutor.cpp"
    "${folly_src_dir}/executors/ManualExecutor.cpp"
    "${folly_src_dir}/executors/MeteredExecutor.cpp"
    "${folly_src_dir}/executors/QueuedImmediateExecutor.cpp"
    "${folly_src_dir}/executors/SerialExecutor.cpp"
    "${folly_src_dir}/executors/StrandExecutor.cpp"
    "${folly_src_dir}/executors/ThreadPoolExecutor.cpp"
    "${folly_src_dir}/executors/ThreadedExecutor.cpp"
    "${folly_src_dir}/executors/TimedDrivableExecutor.cpp"
    "${folly_src_dir}/executors/TimekeeperScheduledExecutor.cpp"
    "${folly_src_dir}/fibers/BatchSemaphore.cpp"
    "${folly_src_dir}/fibers/Baton.cpp"
    "${folly_src_dir}/fibers/Fiber.cpp"
    "${folly_src_dir}/fibers/FiberManager.cpp"
    "${folly_src_dir}/fibers/GuardPageAllocator.cpp"
    "${folly_src_dir}/fibers/Semaphore.cpp"
    "${folly_src_dir}/fibers/SemaphoreBase.cpp"
    "${folly_src_dir}/fibers/SimpleLoopController.cpp"
    "${folly_src_dir}/futures/Barrier.cpp"
    "${folly_src_dir}/futures/Future.cpp"
    "${folly_src_dir}/futures/ManualTimekeeper.cpp"
    "${folly_src_dir}/futures/Promise.cpp"
    "${folly_src_dir}/futures/SharedPromise.cpp"
    "${folly_src_dir}/futures/ThreadWheelTimekeeper.cpp"
    "${folly_src_dir}/futures/detail/Core.cpp"
    "${folly_src_dir}/io/Cursor.cpp"
    "${folly_src_dir}/io/IOBuf.cpp"
    "${folly_src_dir}/io/IOBufQueue.cpp"
    "${folly_src_dir}/io/async/AsyncTimeout.cpp"
    "${folly_src_dir}/io/async/EventBase.cpp"
    "${folly_src_dir}/io/async/EventBaseBackendBase.cpp"
    "${folly_src_dir}/io/async/EventBaseLocal.cpp"
    "${folly_src_dir}/io/async/EventBaseManager.cpp"
    "${folly_src_dir}/io/async/EventHandler.cpp"
    "${folly_src_dir}/io/async/HHWheelTimer.cpp"
    "${folly_src_dir}/io/async/Request.cpp"
    "${folly_src_dir}/io/async/TimeoutManager.cpp"
    "${folly_src_dir}/io/async/VirtualEventBase.cpp"
    "${folly_src_dir}/lang/CString.cpp"
    "${folly_src_dir}/lang/Exception.cpp"
    "${folly_src_dir}/memory/MallctlHelper.cpp"
    "${folly_src_dir}/net/NetOps.cpp"
    "${folly_src_dir}/net/NetOpsDispatcher.cpp"
    "${folly_src_dir}/net/TcpInfo.cpp"
    "${folly_src_dir}/net/detail/SocketFileDescriptorMap.cpp"
    "${folly_src_dir}/portability/SysMembarrier.cpp"
    "${folly_src_dir}/portability/SysUio.cpp"
    "${folly_src_dir}/synchronization/AsymmetricMemoryBarrier.cpp"
    "${folly_src_dir}/synchronization/AtomicNotification.cpp"
    "${folly_src_dir}/synchronization/DistributedMutex.cpp"
    "${folly_src_dir}/synchronization/Hazptr.cpp"
    "${folly_src_dir}/synchronization/HazptrThreadPoolExecutor.cpp"
    # "${folly_src_dir}/synchronization/ParkingLot.cpp"
    "${folly_src_dir}/synchronization/Rcu.cpp"
    "${folly_src_dir}/synchronization/SanitizeThread.cpp"
    "${folly_src_dir}/synchronization/WaitOptions.cpp"
    "${folly_src_dir}/synchronization/detail/Hardware.cpp"
    "${folly_src_dir}/synchronization/detail/Sleeper.cpp"
    "${folly_src_dir}/system/HardwareConcurrency.cpp"
    "${folly_src_dir}/system/Pid.cpp"
    # "${folly_src_dir}/system/ThreadId.cpp"
    "${folly_src_dir}/system/ThreadName.cpp"
    "${folly_src_dir}/tracing/AsyncStack.cpp"
)
target_link_libraries(folly_futures libevent)

## FOLLY FUTURES
#add_library(folly_futures SHARED IMPORTED)
#set_property(TARGET folly_futures PROPERTY
#				IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libfolly_futures.a")

# HERMES
add_library(hermes-engine::libhermes SHARED IMPORTED)
set(hermes_include_dirs
	"${third_party_dir}/hermes/API"
	"${third_party_dir}/hermes/public"
)
set_property(TARGET hermes-engine::libhermes PROPERTY
				IMPORTED_LOCATION "${third_party_dir}/prebuilt/${OHOS_ARCH}/libhermes.so")

# -------- REACT COMMON --------
set(REACT_COMMON_DIR "${third_party_dir}/rn/ReactCommon")
set(REACT_COMMON_PATCH_DIR "${patches_dir}/react_native_core")
add_library(folly_runtime ALIAS folly_target)
add_library(glog ALIAS glog_target)

include_directories(${REACT_COMMON_PATCH_DIR})

# dummy targets added to avoid modyfing CMakeLists located in ReactCommon
add_library(boost INTERFACE)
add_library(log INTERFACE)
add_library(glog_init INTERFACE)
add_library(android INTERFACE)
add_library(fb INTERFACE)
add_library(fbjni INTERFACE)
add_library(reactnativejni INTERFACE)
add_library(mapbufferjni INTERFACE)


function(add_react_common_subdir relative_path)
  add_subdirectory(${REACT_COMMON_DIR}/${relative_path})
endfunction()

add_react_common_subdir(yoga)
add_library(yoga ALIAS yogacore)
add_react_common_subdir(runtimeexecutor)
add_react_common_subdir(reactperflogger)
add_react_common_subdir(logger)
add_react_common_subdir(jsiexecutor)
add_react_common_subdir(cxxreact)
# add_react_common_subdir(jsc)
add_react_common_subdir(jsi)
add_react_common_subdir(butter)
add_react_common_subdir(callinvoker)
add_react_common_subdir(jsinspector)
add_react_common_subdir(hermes/executor)
target_include_directories(hermes_executor_common PRIVATE
	"${folly_include_dir}"
	"${boost_include_dirs}"
	"${hermes_include_dirs}"
)
# add_react_common_subdir(hermes/inspector)
add_react_common_subdir(react/renderer/runtimescheduler)
add_react_common_subdir(react/debug)
add_react_common_subdir(react/config)
add_react_common_subdir(react/renderer/animations)
add_react_common_subdir(react/renderer/attributedstring)
add_react_common_subdir(react/renderer/componentregistry)
add_react_common_subdir(react/renderer/mounting)
add_react_common_subdir(react/renderer/scheduler)
add_react_common_subdir(react/renderer/telemetry)
add_react_common_subdir(react/renderer/templateprocessor)
add_react_common_subdir(react/renderer/uimanager)
add_react_common_subdir(react/renderer/core)
add_react_common_subdir(react/renderer/graphics)
add_react_common_subdir(react/renderer/debug)
add_react_common_subdir(react/renderer/imagemanager)
add_react_common_subdir(react/renderer/components/view)
#add_react_common_subdir(react/renderer/components/switch)
add_subdirectory(${REACT_COMMON_PATCH_DIR}/react/renderer/components/textinput)
# add_react_common_subdir(react/renderer/components/progressbar)
add_react_common_subdir(react/renderer/components/root)
add_react_common_subdir(react/renderer/components/image)
# add_react_common_subdir(react/renderer/components/legacyviewmanagerinterop)
# add_react_common_subdir(react/renderer/componentregistry/native)
add_react_common_subdir(react/renderer/components/text)
# add_react_common_subdir(react/renderer/components/unimplementedview)
add_subdirectory(${REACT_COMMON_PATCH_DIR}/react/renderer/components/rncore)
add_react_common_subdir(react/renderer/components/modal)
add_react_common_subdir(react/renderer/components/scrollview)
add_react_common_subdir(react/renderer/leakchecker)
add_subdirectory(${REACT_COMMON_PATCH_DIR}/react/renderer/textlayoutmanager)
add_react_common_subdir(react/utils)
add_react_common_subdir(react/bridging)
add_react_common_subdir(react/renderer/mapbuffer)
add_react_common_subdir(react/nativemodule/core)
target_include_directories(react_nativemodule_core PRIVATE "${REACT_COMMON_DIR}/callinvoker")

# HERMES INSPECTOR
add_subdirectory("${REACT_COMMON_DIR}/hermes/inspector")
target_include_directories(hermes_inspector PRIVATE
	"${folly_include_dir}"
	"${boost_include_dirs}"
	"${hermes_include_dirs}"
	"${libevent_include_dirs}"
)
target_compile_options(hermes_inspector PRIVATE ${folly_compile_options})

# ----------------------------------------------------------------------------------------------------------------------

add_subdirectory(third-party/aki)

add_library(react_arkui SHARED
	"${RNOH_CPP_DIR}/react_arkui_napi.cpp"
	"${RNOH_CPP_DIR}/react_arkui/native_instance/native_catalyst_instance.cpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/RNOHFabricUIManager.cpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/fabric_mounting_manager.cpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/surface_mounting_manager.cpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/view_manager.hpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/base_view_manager.hpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/view_group_manager.hpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/simple_view_manager.hpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/view_state.cpp"
	"${RNOH_CPP_DIR}/react_arkui/fabric/component_factory.cpp"

	"${RNOH_CPP_DIR}/react_arkui/turbo_module/turbo_module_manager.cpp"
	"${RNOH_CPP_DIR}/react_arkui/turbo_module/TurboModuleFactory.cpp"
	"${RNOH_CPP_DIR}/react_arkui/turbo_module/ArkTSTurboModule.cpp"

	"${RNOH_CPP_DIR}/react_arkui/defaults/DefaultTurboModuleManagerDelegate.cpp"
	"${RNOH_CPP_DIR}/react_arkui/defaults/default_components_registry.cpp"

	"${RNOH_CPP_DIR}/react_arkui/MessageQueueThread.cpp"
	"${RNOH_CPP_DIR}/react_arkui/LogSink.cpp"
	"${RNOH_CPP_DIR}/react_arkui/NativeLogger.cpp"
	"${RNOH_CPP_DIR}/react_arkui/ArkJS.cpp"
	"${RNOH_CPP_DIR}/react_arkui/ShadowViewRegistry.cpp"
	"${RNOH_CPP_DIR}/react_arkui/UIManagerModule.cpp"
	"${RNOH_CPP_DIR}/react_arkui/TextMeasurer.cpp"
	"${RNOH_CPP_DIR}/react_arkui/TaskExecutor/TaskExecutor.cpp"
	"${RNOH_CPP_DIR}/react_arkui/TaskExecutor/NapiTaskRunner.cpp"
	"${RNOH_CPP_DIR}/react_arkui/TaskExecutor/ThreadTaskRunner.cpp"

	"${RNOH_CPP_DIR}/react_core_package/turbo_module/DeviceInfoTurboModule.cpp"
	"${RNOH_CPP_DIR}/react_core_package/turbo_module/SafeAreaTurboModule.cpp"
	"${RNOH_CPP_DIR}/react_core_package/turbo_module/rncore_ModuleProvider.cpp"

	"${RNOH_CPP_DIR}/react_core_package/fabric/rncore_ComponentDescriptorProviderRegistry.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/view/RCTView.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/view/RCTView_manager.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/text/RCTParagraph.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/text/RCTParagraph_manager.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/scroll/RCTScrollView.cpp"
	"${RNOH_CPP_DIR}/react_core_package/fabric/views/scroll/RCTScrollView_manager.cpp"
)
target_include_directories(react_arkui PUBLIC
	"${RNOH_CPP_DIR}"
	"${REACT_COMMON_DIR}"
	"${REACT_COMMON_DIR}/jsiexecutor"
	"${folly_include_dir}"
	"${hermes_include_dirs}"
	"${RNOH_APP_DIR}"
)
target_link_libraries(react_arkui PUBLIC
	libace_napi.z.so
	libhilog_ndk.z.so
	libnative_vsync.so
	libnative_drawing.so
	uv
	Boost::context
	reactnative
	react_render_scheduler
	hermes_executor_common
	rrc_image
	rrc_text
	rrc_textinput
	rrc_scrollview
	rrc_modal
	react_codegen_rncore
	react_nativemodule_core
	react_bridging
	react_render_animations
	libevent
	aki_jsbind
)
target_compile_options(react_arkui PUBLIC ${folly_compile_options}  -DRAW_PROPS_ENABLED -std=c++17)

#reactopenharmony
add_library(reactopenharmony SHARED
 "hello.cpp"
)
target_link_libraries(reactopenharmony PUBLIC
  libace_napi.z.so
)

	