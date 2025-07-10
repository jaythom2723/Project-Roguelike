//
// Created by pengu on 7/9/2025.
//

#include "rotex_context.h"

namespace rotex {
    extern void _add_log_entry(const RTLogType, const std::string&);
}

static RTContext* ctx;

RTContext* rotex::getContext() {
    if (ctx == nullptr) {
        rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Initializing RTContext.");
        ctx = new RTContext();
    }
    return ctx;
}
