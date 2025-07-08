//
// Created by pengu on 7/7/2025.
//

#ifndef ROTEX_H
#define ROTEX_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "rotex_defs.h"

#include <string>
#include <cstdint>

namespace rotex {
    ROTEX_API bool init(std::string& title, uint32_t width, uint32_t height);
    ROTEX_API void close();
}

#endif //ROTEX_H
