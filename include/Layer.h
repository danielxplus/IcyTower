#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Consts.h"

class Layer
{
public:
	Layer();
	Layer(float speed_delta);
	float getViewCenter();
	void render(sf::RenderWindow& window, sf::Drawable& sprite);
	void render(sf::RenderWindow& window, sf::Sprite& drawable);
	void setView(sf::View new_view);
	virtual void reset();
	virtual void logic();

	float cam_posY;
	float speed_delta;
	float step;
	float const_step;
	sf::View view;

protected:
	
};

