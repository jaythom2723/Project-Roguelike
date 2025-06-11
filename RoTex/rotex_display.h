#ifndef ROTEX_DISPLAY_H
#define ROTEX_DISPLAY_H

#include <string>
#include <SDL3/SDL.h>

#include "rotex_defs.h"

class RTDisplay
{
private:
	SDL_Window* hdl;
	SDL_PixelFormat format;

	std::string title;
	int width, height;

	bool close = false;

public:
	ROTEXAPI RTDisplay(const std::string title, const int width, const int height);
	ROTEXAPI ~RTDisplay();

	ROTEXAPI SDL_Window* getHandle();
	ROTEXAPI SDL_PixelFormat getPixelFormat();
	ROTEXAPI const SDL_PixelFormatDetails* getPixelFormatDetails();

	ROTEXAPI std::string getTitle();
	ROTEXAPI int getWidth();
	ROTEXAPI int getHeight();
	ROTEXAPI bool shouldClose();

	ROTEXAPI void setClose(bool value);
};

#endif // ROTEX_DISPLAY_H