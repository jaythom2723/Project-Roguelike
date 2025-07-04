#include "rotex_entity.h"

#include "rotex.h"

// create an entity from text
RTEntity::RTEntity(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, uint8_t* cp437_str, RTColor color)
{
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;
	this->solid = solid;
	this->visible = visible;
	this->collisionMask = collisionMaskLayer;
	// main font is used for entities and background
	texture = new RTTexture(RTMAINFONT, rotex::convertString(cp437_str), color);
}

// create an entity from an image
RTEntity::RTEntity(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, int collisionMaskLayer, SDL_Surface* image)
{
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;
	this->solid = solid;
	this->visible = visible;
	this->collisionMask = collisionMaskLayer;
	texture = new RTTexture(image);
}

RTEntity::~RTEntity()
{
	delete texture;
}

void RTEntity::setVisible(bool value)
{
	visible = value;
}

void RTEntity::setSolid(bool value)
{
	solid = value;
}

void RTEntity::setPos(const RTVec2<float> value)
{
	pos = value;
}

void RTEntity::setX(const float value)
{
	pos.x = value;
}

void RTEntity::setY(const float  value)
{
	pos.y = value;
}

void RTEntity::setScale(const RTVec2<float> value)
{
	scale = value;
}

void RTEntity::setScaleX(const float value)
{
	scale.x = value;
}

void RTEntity::setScaleY(const float value)
{
	scale.y = value;
}

void RTEntity::setRotation(const RTVec2<float> value)
{
	rotation = value;
}

void RTEntity::setRotX(const float value)
{
	rotation.x = value;
}

void RTEntity::setRotY(const float value)
{
	rotation.y = value;
}

void RTEntity::setCell(RTGridCell* cell)
{
	curCell = cell;
}

bool RTEntity::isVisible()
{
	return visible;
}

bool RTEntity::isSolid()
{
	return solid;
}

const int& RTEntity::getId()
{
	return id;
}

RTVec2<float>& RTEntity::getPos()
{
	return pos;
}

RTVec2<float>& RTEntity::getScale()
{
	return scale;
}

RTVec2<float>& RTEntity::getRotation()
{
	return rotation;
}

const int& RTEntity::getCollisionMask()
{
	return collisionMask;
}

RTGridCell* RTEntity::getCell()
{
	return curCell;
}

void RTEntity::update(double deltaTime)
{

}

void RTEntity::draw()
{
	if (!visible)
		return;

	SDL_FRect rect = {};
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = texture->getWidth() * scale.x;
	rect.h = texture->getHeight() * scale.y;

	if (!SDL_RenderTexture(RTRENDERER->getHandle(), texture->getRaw(), nullptr, &rect)) // if we fail to render, print why (usually a texture invalid error)
	{
		std::printf("%s\n", SDL_GetError());
		std::exit(-2);
	}
}