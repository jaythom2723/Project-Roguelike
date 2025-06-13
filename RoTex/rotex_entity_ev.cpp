#include "rotex_entity_ev.h"

RTEntityEV::RTEntityEV(SDL_EventType mask, RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color)
	: RTEntity(pos, scale, rotation, solid, visible, collisionMaskLayer, cp437_str, color)
{
	eventHandler = new RTEventHandler(mask);
}

RTEntityEV::RTEntityEV(SDL_EventType mask, RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, SDL_Surface* image)
	: RTEntity(pos, scale, rotation, solid, visible, collisionMaskLayer, image)
{
	eventHandler = new RTEventHandler(mask);
}

RTEntityEV::~RTEntityEV()
{
	delete eventHandler;
}

RTEventHandler* RTEntityEV::getEventHandler()
{
	return eventHandler;
}