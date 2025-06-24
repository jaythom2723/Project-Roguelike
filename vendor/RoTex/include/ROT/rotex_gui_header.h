#ifndef ROTEX_GUI_HEADER_H
#define ROTEX_GUI_HEADER_H

#include "rotex_gui_text.h"

class RTGUIHeader : public RTGUIText
{
private:
	std::vector<RTTexture*> textures;

public:
	ROTEXAPI RTGUIHeader(std::vector<std::string> texts, std::vector<RTColor> colors);
	ROTEXAPI ~RTGUIHeader();
};

#endif // ROTEX_GUI_HEADER_H