#ifndef ROTEX_GUI_TEXT_H
#define ROTEX_GUI_TEXT_H

#include <string>
#include <vector>
#include <array>

#include "rotex_defs.h"
#include "rotex_color.h"
#include "rotex_texture.h"
#include "rotex_vec.h"

class RTGUIText
{
private:
	std::vector<RTTexture*> textures;

public:
	ROTEXAPI RTGUIText(TTF_Font* font, std::vector<std::string> texts, std::vector<RTColor> colors);
	ROTEXAPI virtual ~RTGUIText();

	ROTEXAPI void setNewTextAt(TTF_Font* font, std::string text, RTColor color, int index);

	ROTEXAPI std::vector<RTTexture*> getTextures();
	ROTEXAPI RTTexture* getTextureAt(int index);
	ROTEXAPI float getWidth();
	ROTEXAPI float getHeight();

	ROTEXAPI void draw(RTVec2<float> pos);
};

#endif // ROTEX_GUI_TEXT_H