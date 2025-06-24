#include "rotex_loader.h"

#include <SDL3_image/SDL_image.h>

#include "rotex_err.h"

TTF_Font* rotex::loadFont(std::string path, float pt_size)
{
	TTF_Font* ret = TTF_OpenFont(path.c_str(), pt_size);
	if (ret == nullptr)
	{
		// if the font isnt found return nullptr and push ASSET_LOAD_FAILURE_ERR to the error stack
		rotex::pushError(rotex::RTErr::ASSET_LOAD_FAILURE_ERR);
		return nullptr;
	}

	return ret; // otherwise, return the font
}

SDL_Surface* rotex::loadImage(std::string path)
{
	SDL_Surface* ret = IMG_Load(path.c_str());
	if (ret == nullptr)
	{
		// if the image isnt found return nullptr and push ASSET_LOAD_FAILURE_ERR to the error stack
		rotex::pushError(rotex::RTErr::ASSET_LOAD_FAILURE_ERR);
		return nullptr;
	}

	return ret; // otherwise, return the image
}