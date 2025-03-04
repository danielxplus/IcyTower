#include "Buttons/Button.h"

Button::Button(sf::Vector2f pos, const std::string& text, Layer& layer)
	:m_layer(layer)
{
	m_rt_text.setPosition(pos);
	m_rt_text.setFont(DefaultFont::getFont());
	m_rt_text.setString(text);
	m_rt_text.setOutlineThickness(const_text_outline_large);
	m_rt_text.setCharacterSize(const_text_menu_size);
	m_rt_text.setLayer(layer);
}

void Button::scale(const sf::Vector2f& value)
{
	m_rt_text.scale(value);
}

void Button::draw(sf::RenderWindow& window)
{
	m_rt_text.render(window);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const
{
	return m_rt_text.isClicked(mousePos);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const
{
	return m_rt_text.isHoveredOn(mousePos);
}

void Button::initRainbow()
{
	m_rt_text.init();
}

void Button::logicRainbow()
{
	m_rt_text.logic();
}

void Button::setText(const std::string& text)
{
	m_rt_text.setString(text);
}


