#pragma once

#include <ReactCommon/TurboModule.h>
#include "react_arkui/turbo_module/ArkTSTurboModule.h"

namespace rnoh {

class JSI_EXPORT DeviceInfoTurboModule : public ArkTSTurboModule {
  public:
	DeviceInfoTurboModule(const ArkTSTurboModule::Context ctx, const std::string name);
};

} // namespace rnoh