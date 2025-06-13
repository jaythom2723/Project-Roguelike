#include "cursor.h"

#include <ROT/rotex.h>

#include "game_state.h"

extern GameState gstate;

Cursor::Cursor(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rot, int collisionMaskLayer, SDL_Surface* image)
	: RTEntityEV(SDL_EVENT_KEY_DOWN, pos, scale, rot, false, false, 1, image)
{

}

Cursor::~Cursor()
{

}

void Cursor::resetPosition()
{
	RTGridCell* ply_cell = RTENTITIES[0]->getCell();
	RTVec2<int> newGridPos = ply_cell->gridPos;
	RTCURSORMAP->moveGridCell(curCell->gridPos, newGridPos);
}

void Cursor::update(double deltaTime)
{
	if (!eventHandler->isEmpty())
	{
		if (eventHandler->getFirst().code != SDL_SCANCODE_C && !gstate.cursorMode)
		{
			eventHandler->clearAll();
			return;
		}

		if (eventHandler->getFirst().code == SDL_SCANCODE_C)
		{	
			gstate.cursorMode = !gstate.cursorMode;
			visible = gstate.cursorMode;
			resetPosition();
		}
		
		RTVec2<int> newGridPos = curCell->gridPos;
		switch (eventHandler->getFirst().code)
		{
		case SDL_SCANCODE_W:
			newGridPos.y -= 1;
			RTCURSORMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_S:
			newGridPos.y += 1;
			RTCURSORMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_D:
			newGridPos.x += 1;
			RTCURSORMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_A:
			newGridPos.x -= 1;
			RTCURSORMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		}
		eventHandler->popFirst();
	}
}