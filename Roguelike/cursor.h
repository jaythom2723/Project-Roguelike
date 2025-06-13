#ifndef CURSOR_H
#define CURSOR_H

#include <ROT/rotex_entity_ev.h>
#include <ROT/rotex_color.h>

struct RTGridCell;

class Cursor : public RTEntityEV
{
private:
	void resetPosition();

public:
	Cursor(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, int collisionMaskLayer, SDL_Surface* image);
	~Cursor();

	void update(double deltaTime);
};

#endif // CURSOR_H