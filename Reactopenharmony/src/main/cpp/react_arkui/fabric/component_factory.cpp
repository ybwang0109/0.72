// 
// Created on 2024/2/8.
// 
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "component_factory.h"
namespace rnoh {
    component_factory::component_factory(){
        LOG(ERROR) << "component_factory::component_factory this is " << this << "\n";
    };
}
