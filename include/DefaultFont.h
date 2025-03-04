#pragma once
#include <SFML/Graphics.hpp>

class DefaultFont
{
public:
	static void init();
	static const sf::Font& getFont();

private:
	static sf::Font m_font;
};
