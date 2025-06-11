#ifndef ROTEX_TEXTURE_H
#define ROTEX_TEXTURE_H

#include "rotex_defs.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <memory>

#include "rotex_color.h"

class RTTexture
{
private:
	SDL_Texture* raw;
	float width, height;

public:
	RTTexture() {}
	ROTEXAPI RTTexture(TTF_Font* f, std::string text, RTColor color);
	ROTEXAPI ~RTTexture();

	ROTEXAPI SDL_Texture* getRaw();
	ROTEXAPI float getWidth();
	ROTEXAPI float getHeight();
};

#endif // ROTEX_TEXTURE_H