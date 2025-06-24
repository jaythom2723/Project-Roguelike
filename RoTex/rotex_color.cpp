#include "rotex_color.h"

#undef RT_CTX_ONLY
#include "rotex.h"

RTColor::RTColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// get the pixel format information form the display
	auto pfd = RTDISPLAY->getPixelFormatDetails();
	Uint32 px = SDL_MapRGBA(pfd, nullptr, r, g, b, a); // map r,g,b,a to a pixel
	SDL_GetRGBA(px, pfd, nullptr, &color.r, &color.g, &color.b, &color.a); // map the pixel color data to the raw SDL_Color
}

RTColor::~RTColor()
{

}

SDL_Color RTColor::getRaw()
{
	return color;
}