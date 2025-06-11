#include "rotex_err.h"

#include <array>
#include <stack>

std::stack<rotex::RTErr> errorStack;

std::array<std::string, 0xFF> errorTranslation = {
	"[ROTEX::ERROR] > Could not initialize SDL3.",
	"[ROTEX::ERROR] > Could not create a display.",
	"[ROTEX::ERROR] > Failed to allocate memory.",
	"[ROTEX::ERROR] > Could not initialize SDL_TTF.",
	"[ROTEX::ERROR] > Could not create a rendering context.",
	"[ROTEX::ERROR] > Could not create a text engine context.",
	"[ROTEX::ERROR] > Could not load an asset.",
	"[ROTEX::ERROR] > Could not create a surface.",
	"[ROTEX::ERROR] > Could not create a texture.",
	"[ROTEX::ERROR] > Could not create a grid map."
};

const std::string rotex::getError()
{
	RTErr code = errorStack.top();
	errorStack.pop();
	return errorTranslation[code];
}

void rotex::pushError(RTErr code)
{
	errorStack.push(code);
}

bool rotex::pushErrRet(RTErr code)
{
	errorStack.push(code);
	return false;
}