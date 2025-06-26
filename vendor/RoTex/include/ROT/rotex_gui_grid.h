#ifndef ROTEX_GUI_2X2GRID_H
#define ROTEX_GUI_2X2GRID_H

#include <vector>
#include <string>

#include "rotex_defs.h"
#include "rotex_color.h"
#include "rotex_vec.h"
#include "rotex_gui_text.h"
#include "rotex_gui_header.h"

class RTGUIGrid
{
private:
	int cols, rows;
	RTGUIHeader* header;
	std::vector<RTGUIText*> textObjects;

public:
	ROTEXAPI RTGUIGrid(int cols, int rows, std::vector<std::string> hdrTexts, std::vector<RTColor> hdrColors, std::vector<std::vector<std::string>> texts, std::vector<std::vector<RTColor>> colors);
	ROTEXAPI ~RTGUIGrid();

	ROTEXAPI std::vector<RTGUIText*> getTextObjects();
	ROTEXAPI RTGUIText* getTextObjectAt(int index);
	ROTEXAPI RTGUIHeader* getHeader();
	ROTEXAPI float getWidth();
	ROTEXAPI float getHeight();

	ROTEXAPI void draw(RTVec2<float> pos);
};

#endif // ROTEX_GUI_2X2GRID_H