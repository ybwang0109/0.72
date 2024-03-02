//
// Created on 2024/2/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#pragma once

#include "react_arkui/LogSink.h"
#include <react/renderer/mounting/ShadowView.h>

using namespace facebook::react;

namespace rnoh {

    template <typename T> class view_manager {

    public:
        T *createView(Tag reactTag, folly::dynamic props, State::Shared state, EventEmitter::Shared eventEmitter);

    protected:
        virtual T *createViewInstance() = 0;
    };

    template <typename T>
    T *view_manager<T>::createView(Tag reactTag, folly::dynamic props, State::Shared state,
                                EventEmitter::Shared eventEmitter) {
        LOG(ERROR) << "view_manager::createView. this is  " << this << "\n";
        auto a = createViewInstance();
        return a;
    }

} // namespace rnoh
