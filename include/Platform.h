#pragma once
#include "Object.h"
#include "Factory.h"
#include "Camera.h"
#include "FloorTypes.h"
#include "DefaultFont.h"
#include "Menu.h"
#include <random>

class Platform : public Object
{
public:
	using Object::Object;
	virtual void setBasic(float& floor, float& y, Layer& layer) override;
	virtual void init() override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void reset() override;
	virtual void logic() override;
	virtual float getPosX() override;
	virtual float getPosY() override;
	virtual float getStartX() override;
	virtual float getEndX() override;
	virtual sf::Sprite& getSprite() override { return platform_sprite; };
	virtual bool collison(sf::Sprite sprite, float m_posX) override;
	virtual void gameOverLogic() override {};

	int getFloor();
	void regenerate();

	int getFloorType(int floor);

private:
	int generatePos();
	int generateLen();

protected:
	bool active_power_up;
	
	float plat_start_pos;
	float plat_end_pos;

	int origin_floor;

	int m_floor;
	int m_length;
	int m_position;

	sf::Sprite platform_sprite;
	sf::Image platform_image;
	sf::Texture platform_texture;
	sf::Text floor_text;
	std::vector<sf::IntRect> m_vector;
	sf::Image floor_sign;
	sf::Sprite floor_sign_sprite;

	//global values for logic iteretions
	int counter = 0;
	bool activated = false;
};