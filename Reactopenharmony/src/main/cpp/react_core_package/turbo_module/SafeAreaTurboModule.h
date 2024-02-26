#pragma once

#include "react_arkui/turbo_module/ArkTSTurboModule.h"

namespace rnoh {

class JSI_EXPORT SafeAreaTurboModule : public ArkTSTurboModule {
  public:
    SafeAreaTurboModule(const ArkTSTurboModule::Context ctx, const std::string name);
};

} // namespace rnoh