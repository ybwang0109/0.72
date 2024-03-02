//
// Created on 2024/2/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "react_arkui/fabric/base_view_manager.hpp"

namespace rnoh {

    template <typename T> class view_group_manager: public base_view_manager<T> {};
}
