#ifndef ROTEX_ENTITY_H
#define ROTEX_ENTITY_H

#include "rotex_vec.h"
#include "rotex_texture.h"
#include "rotex_color.h"

struct RTGridCell;

class RTEntity
{
protected:
	int id;

	int collisionMask;

	bool visible;
	bool solid;

	// transform
	RTVec2<float> pos = RTVEC2FZERO;
	RTVec2<float> scale = RTVEC2FZERO;
	RTVec2<float> rotation = RTVEC2FZERO;

	// texture
	RTTexture* texture;

	RTGridCell* curCell = nullptr;

public:
	RTEntity() {}
	ROTEXAPI RTEntity(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color);
	ROTEXAPI RTEntity(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, SDL_Surface* img);
	ROTEXAPI virtual ~RTEntity();

	ROTEXAPI void setVisible(bool value);
	ROTEXAPI void setSolid(bool value);
	ROTEXAPI void setPos(const RTVec2<float> value);
	ROTEXAPI void setX(const float value);
	ROTEXAPI void setY(const float value);
	ROTEXAPI void setScale(const RTVec2<float> value);
	ROTEXAPI void setScaleX(const float value);
	ROTEXAPI void setScaleY(const float value);
	ROTEXAPI void setRotation(const RTVec2<float> value);
	ROTEXAPI void setRotX(const float value);
	ROTEXAPI void setRotY(const float value);
	ROTEXAPI void setCell(RTGridCell* cell);

	ROTEXAPI bool isVisible();
	ROTEXAPI bool isSolid();

	ROTEXAPI const int& getId();
	ROTEXAPI RTVec2<float>& getPos();
	ROTEXAPI RTVec2<float>& getScale();
	ROTEXAPI RTVec2<float>& getRotation();
	ROTEXAPI const int& getCollisionMask();
	ROTEXAPI RTGridCell* getCell();

	ROTEXAPI virtual void update(double deltaTime);
	ROTEXAPI virtual void draw();
};

#endif // ROTEX_ENTITY_H