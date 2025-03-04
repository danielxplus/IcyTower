#include "WallLeft.h"

bool registerWallL = Factory::registerit("WallLeft", []() -> std::unique_ptr<Object> { return std::make_unique<WallLeft>(); });

void WallLeft::setBasic(float& x, float& y, Layer& layer)
{
	
	this->m_layer = layer;
	this->m_positionX = x;
	this->m_positionY = y;
	
	this->m_sprite.setPosition(m_positionX, m_positionY);
}

void WallLeft::init()
{
	this->m_sprite.setTexture(this->m_assets.getTexture("wall_left"));
}

void WallLeft::render(sf::RenderWindow& window)
{
	this->m_sprite.setPosition(m_positionX, Game::m_platforms[0].get()->m_layer.cam_posY);
	m_layer.render(window, this->m_sprite);
}

void WallLeft::reset()
{
	this->m_sprite.setPosition(m_positionY, m_positionY);
}

void WallLeft::logic()
{
	//
}
