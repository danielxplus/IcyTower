#include "WallRight.h"

bool registerWallR = Factory::registerit("WallRight", []() -> std::unique_ptr<Object> { return std::make_unique<WallRight>(); });

void WallRight::setBasic(float& x, float& y, Layer& layer)
{
	this->m_layer = layer;
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_sprite.setPosition(m_positionX, m_positionY);
}

void WallRight::init()
{
	this->m_sprite.setTexture(this->m_assets.getTexture("wall_right"));
}

void WallRight::render(sf::RenderWindow& window)
{
	this->m_sprite.setPosition(m_positionX, Game::m_platforms[0].get()->m_layer.cam_posY);
	m_layer.render(window, this->m_sprite);
}

void WallRight::reset()
{
	this->m_sprite.setPosition(m_positionY, m_positionY);
}

void WallRight::logic()
{
	//
}

