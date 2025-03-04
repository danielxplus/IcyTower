#pragma once

#include <SFML/Graphics.hpp>
#include "EyeCandy.h"
#include "Layer.h"
#include <vector>

class EyeCandyEngine
{
public:
	EyeCandyEngine();
	void addCandy(const float& posX, const float& posY, int count);
	void addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, int count);
	void addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed, int count);
	void resetCandy();
	void logic();
	void render(sf::RenderWindow& window, bool _reset);
	void setLayer(Layer& _layer);
	int getCount();
	void reset();

private:
	std::vector<EyeCandy> m_engine;
	std::vector<EyeCandy> m_passive_engine;
	Layer* m_layer;
};