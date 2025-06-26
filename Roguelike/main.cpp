#include <iostream>

#include <ROT/rotex.h>
#include <ROT/rotex_gui_header.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game_state.h"
#include "player.h"
#include "cursor.h"

GameState gstate = { 0 };
RTGUIHeader* header = nullptr;
RTGUIText* text = nullptr;
RTGUIText* hp_test = nullptr;

void event_loop(SDL_Event& e);
void update(double deltaTime);
void draw();

int main()
{
	if (!rotex::init("Project: Roguelike", 960, 560))
	{
		std::printf("%s - %s\n", rotex::getError().c_str(), SDL_GetError());
		return -1;
	}
	
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaffffffffffffffffffffffffffffffff```` - coconut shrimp

	gstate.cursorMode = false;

	uint8_t cp437_str[] = { 0x01, 0x00 };
	gstate.player = rotex::createEntity<Player>(RTVEC2FZERO, RTVec2<float>(1.f, 1.f), RTVEC2FZERO, true, true, 0, cp437_str, RTCOL_GREEN);
	RTGRIDMAP->setGridCell(RTVec2<int>(0, 0), gstate.player);
	gstate.player->setPos(RTGRIDMAP->gridCellToWorldPosition(RTVec2<int>(0, 0)));

	gstate.cursor = rotex::createEntity<Cursor>(RTVEC2FZERO, RTVec2<float>(1.f, 1.f), RTVEC2FZERO, 1, rotex::loadImage("gfx/images/cursor.png"));
	RTCURSORMAP->setGridCell(RTVec2<int>(RTGRIDMAP_COLS-1, RTGRIDMAP_ROWS-1), gstate.cursor);
	gstate.cursor->setPos(RTCURSORMAP->gridCellToWorldPosition(RTVec2<int>(RTGRIDMAP_COLS - 1, RTGRIDMAP_ROWS - 1)));

	std::uint64_t last, now;
	double deltaTime;

	last = 0;
	now = SDL_GetPerformanceCounter();

	SDL_Event e;
	while (!RTDISPLAY->shouldClose())
	{
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

		rotex::eventLoop(e, event_loop);
		update(deltaTime);
		draw();

		SDL_RenderPresent(RTRENDERER->getHandle());
	}

	delete header;
	delete text;
	rotex::close();

	return 0;
}

void event_loop(SDL_Event& e)
{
	// old event_loop moved to rotex::eventLoop();

	if (e.type == SDL_EVENT_KEY_DOWN)
	{
		if (e.key.scancode == SDL_SCANCODE_SPACE)
		{
			std::pair<int, int> curHP = gstate.player->getHitpoints();
			std::printf("%d -> %d\n", curHP.first, curHP.first - 10);
			curHP.first -= 10;
			gstate.player->setHitpoints(curHP);
			// hp_test->setNewTextAt(RTGUIFONT, std::to_string(curHP.first), RTCOL_RED, 1);
		}
	}
}

void update(double deltaTime) 
{
	for (auto ent : RTENTITIES)
		ent->update(deltaTime);
}

void draw()
{
	SDL_RenderClear(RTRENDERER->getHandle());

	RTGRIDMAP->draw();
	RTCURSORMAP->draw();
	
	// draw the border of the grid-map
	SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderLine(RTRENDERER->getHandle(), RTGRIDMAP_WIDTH_PX, 0, RTGRIDMAP_WIDTH_PX, RTGRIDMAP_HEIGHT_PX);
	SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0x00, 0x00, 0x00, 0xff);
}