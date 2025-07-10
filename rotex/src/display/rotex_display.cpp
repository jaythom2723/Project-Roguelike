//
// Created by pengu on 7/8/2025.
//

#include "display/rotex_display.h"

RTDisplay::RTDisplay(const std::string& title, const uint32_t width, const uint32_t height)
{
    this->title = title;
    this->width = width;
    this->height = height;

    handle = SDL_CreateWindow(title.c_str(), static_cast<int>(width), static_cast<int>(height), 0);
    if (handle == nullptr) {
        return; // TODO: implement error handling
    }

    renderHandle = SDL_CreateRenderer(handle, nullptr);
    if (renderHandle == nullptr) {
        return; // TODO: implement error handling
    }

    textEngineHandle = TTF_CreateRendererTextEngine(renderHandle);
    if (textEngineHandle == nullptr) {
        return; // TODO: implement error handling
    }
}

RTDisplay::~RTDisplay() {
    TTF_DestroyRendererTextEngine(textEngineHandle);
    SDL_DestroyRenderer(renderHandle);
    SDL_DestroyWindow(handle);
}

const SDL_PixelFormatDetails* RTDisplay::getPFD() const {
    return SDL_GetPixelFormatDetails(SDL_GetWindowPixelFormat(handle));
}