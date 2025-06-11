#ifndef PLAYER_H
#define PLAYER_H

#include <ROT/rotex_entity_ev.h>

class Player : public RTEntityEV
{
private:

public:
	Player(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, uint8_t* cp437_str, RTColor color);
	~Player();

	void update(double deltaTime);
};

#endif // PLAYER_H