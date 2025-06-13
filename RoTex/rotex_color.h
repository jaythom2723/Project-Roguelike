#ifndef ROTEX_COLOR_H
#define ROTEX_COLOR_H

#include "rotex_defs.h"

#include <SDL3/SDL.h>

#define RTCOL_WHITE RTColor(0xff, 0xff, 0xff, 0xff)
#define RTCOL_BLACK RTColor(0x00, 0x00, 0x00, 0xff)
#define RTCOL_RED RTColor(0xff, 0x00, 0x00, 0xff)
#define RTCOL_GREEN RTColor(0x00, 0xff, 0x00, 0xff)
#define RTCOL_BLUE RTColor(0x00, 0x00, 0xff, 0xff)
#define RTCOL_DODGERBLUE RTColor(0x1e, 0x90, 0xff, 0xff)
#define RTCOL_PURPLE RTColor(0x52, 0x00, 0xff, 0xff)
#define RTCOL_YELLOW RTColor(0xff, 0xff, 0x00, 0xff)
#define RTCOL_CLEAR RTColor(0x00, 0x00, 0x00, 0x00)

class RTColor
{
private:
	SDL_Color color;

public:
	RTColor() {}
	ROTEXAPI RTColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	ROTEXAPI ~RTColor();

	ROTEXAPI SDL_Color getRaw();
};

#endif // ROTEX_COLOR_H