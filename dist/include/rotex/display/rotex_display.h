//
// Created by pengu on 7/8/2025.
//

#ifndef ROTEX_DISPLAY_H
#define ROTEX_DISPLAY_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

#include "rotex_defs.h"

class RTDisplay {
private:
    SDL_Window* handle;
    SDL_Renderer* renderHandle;
    TTF_TextEngine* textEngineHandle;

    std::string title;
    int width, height;

    bool close = false;

public:
    /* Constructor - RTDisplay()
     * :param: const std::string& title
     *         - The title to set the SDL_Window to
     * :param: uint32_t width
     *         - The width to set the SDL_Window to
     * :param: uint32_t height
     *         - The height to set the SDL_Window to
     */
    ROTEX_API RTDisplay(const std::string& title, uint32_t width, uint32_t height);
    ROTEX_API ~RTDisplay();

    ROTEX_API const SDL_PixelFormatDetails* getPFD() const;

    const std::string& getTitle() const { return title; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setClose(const bool value) { close = value; }
    bool shouldClose() const { return close; }

    SDL_Window* getHandle() const { return handle; }
    SDL_Renderer* getRenderHandle() const { return renderHandle; }
    TTF_TextEngine* getTextEngineHandle() const { return textEngineHandle; }
};

#endif //ROTEX_DISPLAY_H
