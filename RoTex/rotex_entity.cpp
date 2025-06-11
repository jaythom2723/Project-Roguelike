#include "rotex_entity.h"

#include "rotex.h"

RTEntity::RTEntity(RTVec2<float> pos, RTVec2<float> scale, RTVec2<float> rotation, bool solid, bool visible, uint8_t* cp437_str, RTColor color)
{
	this->pos = pos;
	this->scale = scale;
	this->rotation = rotation;
	this->solid = solid;
	this->visible = visible;
	texture = new RTTexture(RTMAINFONT, rotex::convertString(cp437_str), color);
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

	if (!SDL_RenderTexture(RTRENDERER->getHandle(), texture->getRaw(), nullptr, &rect))
	{
		std::printf("%s\n", SDL_GetError());
		std::exit(-2);
	}
}