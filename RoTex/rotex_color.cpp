#include "rotex_color.h"

#undef RT_CTX_ONLY
#include "rotex.h"

RTColor::RTColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	auto pfd = rotex::getContext()->display->getPixelFormatDetails();
	Uint32 px = SDL_MapRGBA(pfd, nullptr, r, g, b, a);
	SDL_GetRGBA(px, pfd, nullptr, &color.r, &color.g, &color.b, &color.a);
}

RTColor::~RTColor()
{

}

SDL_Color RTColor::getRaw()
{
	return color;
}