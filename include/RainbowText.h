#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Layer.h"
#include "DefaultFont.h"

class RainbowText : public sf::Text
{
public:
    using sf::Text::Text;
    static sf::Color changeColor(const sf::Color& color, int delta);
    void init();
    void reset();
    void setLayer(Layer& _layer);
    void logic();
    void render(sf::RenderWindow& window);
    void scale(const sf::Vector2f& size);

    bool isClicked(const sf::Vector2f mousePos) const;
    bool isHoveredOn(const sf::Vector2f &mousePos) const;

    void setVisible(bool visible) { m_visible = visible; }
    bool isVisible() const { return m_visible; }

private:
    bool m_initialized { false };
    bool m_initialized_colors { false };
    bool m_initialized_chars { false };
    sf::Text m_comp;
    int m_color_num{ 18 };
    int m_char_num{ 0 };
    std::vector<sf::Text> m_chars;
    std::vector<sf::Color> m_colors;
    Layer* m_layer{ nullptr };

    bool m_magic_skipper;
    bool m_visible = true;
    int m_magicY{ 0 };
    int  m_magicX;
};

