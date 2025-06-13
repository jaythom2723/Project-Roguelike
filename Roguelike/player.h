#ifndef PLAYER_H
#define PLAYER_H

#include <ROT/rotex_entity_ev.h>
#include "cursor.h"

class Player : public RTEntityEV
{
public:
	Player(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color);
	~Player();

	void update(double deltaTime);
};

#endif // PLAYER_H