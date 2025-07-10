//
// Created by pengu on 7/9/2025.
//

#ifndef ROTEX_CONTEXT_H
#define ROTEX_CONTEXT_H

#include <memory>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "rotex_defs.h"
#include "display/rotex_display.h"

// RTContext does not have a constructor, everything must be initialized manually
struct RTContext
{
    std::unique_ptr<RTDisplay> display;
    lua_State* L;
};

namespace rotex {
    // auto-initializes the context if its nullptr
    ROTEX_API RTContext* getContext();
}

#endif //ROTEX_CONTEXT_H
