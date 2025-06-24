#include "rotex_gui_header.h"

#include "rotex.h"

#include <SDL3/SDL.h>

RTGUIHeader::RTGUIHeader(std::vector<std::string> texts, std::vector<RTColor> colors)
	: RTGUIText(RTGUIHEADERFONT, texts, colors)
{

}

RTGUIHeader::~RTGUIHeader()
{
	for (auto tex : textures)
	{
		if (tex == nullptr)
			break;

		delete tex;
	}
}