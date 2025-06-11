#include "rotex_display.h"

#include "rotex_defs.h"
#include "rotex_err.h"

#include <cstdlib>

RTDisplay::RTDisplay(const std::string title, const int width, const int height)
{
	this->title = title;
	this->width = width;
	this->height = height;

	hdl = SDL_CreateWindow(title.c_str(), width, height, 0);
	if (hdl == nullptr)
	{
		rotex::pushError(rotex::RTErr::DISPLAY_CREATE_ERR);
		return;
	}

	format = SDL_GetWindowPixelFormat(hdl);
}

RTDisplay::~RTDisplay()
{
}

SDL_Window* RTDisplay::getHandle()
{
	return hdl;
}

SDL_PixelFormat RTDisplay::getPixelFormat()
{
	return format;
}

const SDL_PixelFormatDetails* RTDisplay::getPixelFormatDetails()
{
	return SDL_GetPixelFormatDetails(format);
}

std::string RTDisplay::getTitle()
{
	return title;
}

int RTDisplay::getWidth()
{
	return width;
}

int RTDisplay::getHeight()
{
	return height;
}

bool RTDisplay::shouldClose()
{
	return close;
}

void RTDisplay::setClose(bool value)
{
	close = value;
}