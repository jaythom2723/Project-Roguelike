#include "rotex_texture.h"

#include "rotex.h"

RTTexture::RTTexture(TTF_Font* f, std::string text, RTColor color)
{
	SDL_Surface* txtSurface = TTF_RenderText_Shaded(f, text.c_str(), text.size(), color.getRaw(), RTCOL_BLACK.getRaw());
	if (txtSurface == nullptr)
	{
		rotex::pushError(rotex::RTErr::SURFACE_CREATE_ERR);
		return;
	}

	raw = SDL_CreateTextureFromSurface(RTRENDERER->getHandle(), txtSurface);
	if (raw == nullptr)
	{
		rotex::pushError(rotex::RTErr::TEXTURE_CREATE_ERR);
		return;
	}

	SDL_SetTextureBlendMode(raw, SDL_BLENDMODE_BLEND);
	SDL_DestroySurface(txtSurface);
	SDL_GetTextureSize(raw, &width, &height);
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