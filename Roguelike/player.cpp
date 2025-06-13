#include "player.h"

#include <SDL3/SDL.h>
#include <ROT/rotex.h>

#include "game_state.h"

extern GameState gstate;

Player::Player(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color)
	: RTEntityEV(SDL_EVENT_KEY_DOWN, pos, scale, rotation, solid, visible, collisionMaskLayer, cp437_str, color)
{

}

Player::~Player()
{

}

void Player::update(double deltaTime)
{
	if (gstate.cursorMode)
	{
		eventHandler->clearAll();
	}

	if (gstate.cursorMode == false && !eventHandler->isEmpty())
	{
		RTVec2<int> newGridPos = curCell->gridPos;
		switch (eventHandler->getFirst().code)
		{
		case SDL_SCANCODE_W:
			newGridPos.y -= 1;
			RTGRIDMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_S:
			newGridPos.y += 1;
			RTGRIDMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_A:
			newGridPos.x -= 1;
			RTGRIDMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		case SDL_SCANCODE_D:
			newGridPos.x += 1;
			RTGRIDMAP->moveGridCell(curCell->gridPos, newGridPos);
			break;
		}
		eventHandler->popFirst();
	}
}
