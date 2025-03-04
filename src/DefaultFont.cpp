#include "DefaultFont.h"

sf::Font DefaultFont::m_font;

void DefaultFont::init()
{
	m_font.loadFromFile("font.ttf");
}
const sf::Font& DefaultFont::getFont()
{
	return m_font;
}