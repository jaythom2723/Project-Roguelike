#ifndef ROTEX_DEFS_H
#define ROTEX_DEFS_H

#ifdef ROTEX_EXPORTS
#define ROTEXAPI __declspec(dllexport)
#else
#define ROTEXAPI __declspec(dllimport)
#endif // ROTEX_EXPORTS

#include <SDL3/SDL.h>

namespace rotex
{
	typedef enum {
		SDL_INIT_ERR,
		DISPLAY_CREATE_ERR,
		MEM_ALLOC_ERR,
		TTF_INIT_ERR,
		RENDERER_CREATE_ERR,
		TEXT_ENGINE_CREATE_ERR,
		ASSET_LOAD_FAILURE_ERR,
		SURFACE_CREATE_ERR,
		TEXTURE_CREATE_ERR,
		GRIDMAP_CREATE_ERR
	} RTErr;

	typedef struct {
		SDL_EventType type;
		union {
			SDL_Scancode code;
		};
	} RTEvent;
}

#endif // ROTEX_DEFS_H