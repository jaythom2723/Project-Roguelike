#include <iostream>

#undef RT_CTX_ONLY
#include <ROT/rotex.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "player.h"

void event_loop(SDL_Event& e);
void update(double deltaTime);
void draw();

int main()
{
	if (!rotex::init("test", 640, 480))
	{
		std::printf("%s - %s\n", rotex::getError().c_str(), SDL_GetError());
		return -1;
	}
	
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaffffffffffffffffffffffffffffffff```` - coconut shrimp

	uint8_t cp437_str[] = { 0x01, 0x00 };
	rotex::createEntity<Player>(RTVEC2FZERO, RTVec2<float>(1.f, 1.f), RTVEC2FZERO, true, true, cp437_str, RTCOL_GREEN);
	RTGRIDMAP->setGridCell(RTVec2<int>(0, 0), RTENTITIES[0]);
	RTENTITIES[0]->setPos(RTGRIDMAP->gridCellToWorldPosition(RTVec2<int>(0, 0)));

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

		event_loop(e);
		update(deltaTime);
		draw();
	}

	rotex::close();

	return 0;
}

// this should definitely be an internal engine function
void event_loop(SDL_Event& e)
{
	int i;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
		{
			RTDISPLAY->setClose(true);
			return;
		}

		for (i = 0; i < RTENTITIES.size(); i++)
		{
			std::shared_ptr<RTEntityEV> ent = std::dynamic_pointer_cast<RTEntityEV>(RTENTITIES[i]);
			if (ent.get() == nullptr)
				continue; // move to next entity if cannot convert to RTEntityEV

			rotex::RTEvent event = {};
			event.type = (SDL_EventType)e.type;

			switch (e.type)
			{
			case SDL_EVENT_KEY_DOWN:
				event.code = e.key.scancode;
				break;
			}

			ent->getEventHandler()->pushEvent(event);
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

	SDL_RenderPresent(RTRENDERER->getHandle());
}