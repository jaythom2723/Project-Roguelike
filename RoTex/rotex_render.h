#ifndef ROTEX_RENDER_H
#define ROTEX_RENDER_H

#include "rotex_defs.h"
#include "rotex_entity.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>

class RTRenderer
{
private:
	SDL_Renderer* hdl;
	TTF_TextEngine* txtHdl;

public:
	ROTEXAPI RTRenderer();
	ROTEXAPI ~RTRenderer();

	ROTEXAPI SDL_Renderer* getHandle();
	ROTEXAPI TTF_TextEngine* getTextHandle();
};

#endif // ROTEX_RENDER