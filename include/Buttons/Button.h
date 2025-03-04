#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "RainbowText.h"
#include "Consts.h"
#include <string>

class Button
{
public:
	Button(sf::Vector2f pos,const std::string &text, Layer& layer);
	virtual ~Button() = default;
	void scale(const sf::Vector2f &value);
	void draw(sf::RenderWindow& window);
	bool isClicked(const sf::Vector2f& mousePos) const;
	bool isHovered(const sf::Vector2f& mousePos) const;
	void initRainbow();
	void logicRainbow();
	void setText(const std::string& text);

	virtual void action(sf::RenderWindow& window,Layer &layer) = 0;

private:
	Layer m_layer;
	RainbowText m_rt_text;

};