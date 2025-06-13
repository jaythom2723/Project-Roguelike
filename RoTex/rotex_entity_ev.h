#ifndef ROTEX_ENTITY_EV_H
#define ROTEX_ENTITY_EV_H

#include "rotex_defs.h"
#include "rotex_vec.h"
#include "rotex_color.h"
#include "rotex_event_handler.h"
#include "rotex_entity.h"

class RTEntityEV : public RTEntity
{
protected:
	RTEventHandler* eventHandler;

public:
	ROTEXAPI RTEntityEV(SDL_EventType mask, RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color);
	ROTEXAPI RTEntityEV(SDL_EventType mask, RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, SDL_Surface* image);
	ROTEXAPI virtual ~RTEntityEV();

	ROTEXAPI RTEventHandler* getEventHandler();
};

#endif // ROTEX_ENTITY_EV_H