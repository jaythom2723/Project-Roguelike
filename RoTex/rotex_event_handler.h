#ifndef ROTEX_EVENT_HANDLER_H
#define ROTEX_EVENT_HANDLER_H

#include <SDL3/SDL.h>

#include <vector>
#include <queue>

#include "rotex_defs.h"

#define ROTEX_MAX_EVENT_MASKS 0xff

class RTEventHandler
{
private:
	SDL_EventType eventMask;
	std::queue<rotex::RTEvent> event_queue;

public:
	ROTEXAPI RTEventHandler(SDL_EventType eventMask);
	ROTEXAPI ~RTEventHandler();

	ROTEXAPI const rotex::RTEvent& getFirst();
	ROTEXAPI void popFirst();
	ROTEXAPI void pushEvent(const rotex::RTEvent event);
	ROTEXAPI bool isEmpty();
};

#endif // ROTEX_EVENT_HANDLER_H