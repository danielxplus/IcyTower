#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Assets.h"
#include "Layer.h"

class Object
{
public:
	Object();
    ~Object() = default;
	virtual void init() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void reset() = 0;
	virtual void logic() = 0;
	virtual void setBasic(float &x, float &y, Layer& layer) = 0;
	virtual float getPosX() = 0;
	virtual float getPosY() = 0;
	virtual float getStartX() = 0;
	virtual float getEndX() = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual bool collison(sf::Sprite sprite, float m_posX) = 0;
	virtual void gameOverLogic() = 0;

	Layer& m_layer;
	
protected:
	Assets m_assets = m_assets.getInstance();
	sf::Texture m_texture;
	float m_positionY;
	float m_positionX;
	sf::Sprite m_sprite;
	
};

