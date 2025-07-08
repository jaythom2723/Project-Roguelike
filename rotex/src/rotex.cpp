//
// Created by pengu on 7/7/2025.
//

#include "rotex.h"

using namespace rotex;

bool init(const std::string& title, const uint32_t width, const uint32_t height) {
    if (!SDL_Init(SDL_INIT_VIDEO))
        return false; // failed to init SDL

    // TODO: create the context and create it all

    return true;
}

void close() {
    SDL_Quit();
}
