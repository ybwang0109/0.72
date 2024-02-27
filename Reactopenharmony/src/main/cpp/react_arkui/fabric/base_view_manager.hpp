//
// Created on 2024/2/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once

#include "react_arkui/fabric/view_manager.hpp"

namespace rnoh {

    template <typename T> class base_view_manager : public view_manager<T> {};

} // namespace rnoh