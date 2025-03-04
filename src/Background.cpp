#include "Background.h"

void Background::setBasic(float& x, float& y, Layer& layer)
{
	this->m_layer = layer;
	this->m_positionX = x;
	this->m_positionY = y;
	this->m_sprite.setPosition(m_positionX, m_positionY);
}

void Background::init()
{
	this->m_sprite.setTexture(this->m_assets.getTexture("game_bg"));
}

void Background::render(sf::RenderWindow& window)
{
	this->m_sprite.setPosition(m_positionX, Game::m_platforms[0].get()->m_layer.cam_posY);
	m_layer.render(window, this->m_sprite);
}

void Background::reset()
{
	this->m_sprite.setPosition(m_positionY, m_positionY);
}

void Background::logic()
{
	
}