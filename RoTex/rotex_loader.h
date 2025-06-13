#ifndef ROTEX_LOADER_H
#define ROTEX_LOADER_H

#include "rotex_defs.h"

#include <string>

#include <SDL3_ttf/SDL_ttf.h>

namespace rotex
{
	ROTEXAPI TTF_Font* loadFont(std::string path, float pt_size);
	ROTEXAPI SDL_Surface* loadImage(std::string path);
}

#endif // ROTEX_LOADER_H