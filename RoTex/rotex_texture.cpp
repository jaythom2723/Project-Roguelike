#include "rotex_texture.h"

#include "rotex.h"

// create a texture from a string of text, with an associate font from SDL3_ttf
RTTexture::RTTexture(TTF_Font* f, std::string text, RTColor color)
{
	// create the text surface
	SDL_Surface* txtSurface = TTF_RenderText_Shaded(f, text.c_str(), text.size(), color.getRaw(), RTCOL_CLEAR.getRaw());
	if (txtSurface == nullptr) // if nullptr, push SURFACE_CREATE_ERR to the error stack, and do nothing
	{
		rotex::pushError(rotex::RTErr::SURFACE_CREATE_ERR);
		return;
	}

	// create the raw SDL_Texture data from the surface
	raw = SDL_CreateTextureFromSurface(RTRENDERER->getHandle(), txtSurface);
	if (raw == nullptr) // if nullptr, push TEXTURE_CREATE_ERR to the error stack, and do nothing
	{
		rotex::pushError(rotex::RTErr::TEXTURE_CREATE_ERR);
		return;
	}

	// allow the texture to be colored
	SDL_SetTextureBlendMode(raw, SDL_BLENDMODE_BLEND);
	SDL_DestroySurface(txtSurface); // destroy the unneeded SDL_Surface
	SDL_GetTextureSize(raw, &width, &height); // set width and height
}

// create a texture from a loaded image from SDL3_image
RTTexture::RTTexture(SDL_Surface* img)
{
	// since we already have a surface, create the raw SDL_Texture data
	raw = SDL_CreateTextureFromSurface(RTRENDERER->getHandle(), img);
	if (raw == nullptr) // if nullptr, push TEXTURE_CREATE_ERR to the error stack, and do nothing
	{
		rotex::pushError(rotex::RTErr::TEXTURE_CREATE_ERR);
		return;
	}

	// allow the new texture to get colored
	SDL_SetTextureBlendMode(raw, SDL_BLENDMODE_BLEND);
	SDL_DestroySurface(img); // destroy the unneeded surface
	SDL_GetTextureSize(raw, &width, &height); // set width and height
}

RTTexture::~RTTexture()
{
	SDL_DestroyTexture(raw);
}

SDL_Texture* RTTexture::getRaw()
{
	return raw;
}

float RTTexture::getWidth()
{
	return width;
}

float RTTexture::getHeight()
{
	return height;
}