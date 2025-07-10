//
// Created by pengu on 7/9/2025.
//

#include <stack>
#include <string>
#include <iostream>

#include <SDL3/SDL.h>

#include "rotex.h"
#include "rotex_defs.h"

namespace rotex {
    extern void _add_log_entry(const RTLogType, const std::string&);
}

static std::stack<std::pair<RTErrType, std::string>> errors;

/*
 * error message log message template
 * [ROTEX_ERR:<RTErrType>] > "<preset-error-msg>" - "<custom-error-msg>"
 */

// _ denotes private API functions that should never be exposed to the user (game programmer)
namespace rotex {
    bool _assert(const bool cond, RTErrType type, const std::string& msg) {
        if (cond) // if the condition doesn't fail, exit prematurely
            return true;

        errors.emplace(type, msg + " | " + SDL_GetError());
        _add_log_entry(RTLogType::ROTEX_LOG_ERROR, msg + " | " + SDL_GetError());
        return false; // condition failed, therefore return false
    }

    const std::string& _get_error() {
        if (errors.empty())
            return "";

        // get the most recent error from the stack
        const std::string& top = errors.top().second;
        errors.pop();
        return top;
    }
}
