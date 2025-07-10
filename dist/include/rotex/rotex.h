//
// Created by pengu on 7/7/2025.
//

#ifndef ROTEX_H
#define ROTEX_H

#include <string>

#include "rotex_defs.h"
#include "display/rotex_display.h"
#include "rotex_context.h"

#define RTCTX rotex::getContext()

namespace rotex {
    ROTEX_API bool init();
    ROTEX_API void close();
}

#endif //ROTEX_H
