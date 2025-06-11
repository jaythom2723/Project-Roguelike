#include "rotex_event_handler.h"

RTEventHandler::RTEventHandler(SDL_EventType eventMask)
{
	this->eventMask = eventMask;
}

RTEventHandler::~RTEventHandler()
{

}

const rotex::RTEvent& RTEventHandler::getFirst()
{
	return event_queue.front();
}

void RTEventHandler::popFirst()
{
	event_queue.pop();
}

void RTEventHandler::pushEvent(const rotex::RTEvent event)
{
	if (event.type == eventMask)
		event_queue.push(event);
}

bool RTEventHandler::isEmpty()
{
	return event_queue.empty();
}