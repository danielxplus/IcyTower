#pragma once
#include "Object.h"
#include "Factory.h"
#include "Game.h"

class WallLeft : public Object
{
public:
	using Object::Object;

	virtual void setBasic(float& x, float& y ,Layer & layer) override;
	virtual void init() override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void reset() override;
	virtual void logic() override;
	virtual float getPosX() override { return 0; };
	virtual float getPosY() override { return 0; };
	virtual float getStartX() override { return 0; };
	virtual float getEndX() override { return 0; };
	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual bool collison(sf::Sprite sprite, float m_posX) override { return false; };
	virtual void gameOverLogic() override {};

private:

};