#include "RainbowText.h"

//=======================================================================
void RainbowText::init()
{
    m_initialized_colors = false;
    m_initialized_chars = false;
    m_chars.clear();
    m_colors.clear();

    m_char_num = this->getString().getSize();
    m_chars.reserve(m_char_num);
    for (int i = 0; i < m_char_num; ++i)
    {
        m_chars.emplace_back(this->getString().substring(i, 1), DefaultFont::getFont(), this->getCharacterSize());
    }
    m_comp = *this;

    while (m_color_num < m_char_num)
    {
        m_color_num += 18;
    }

    m_magic_skipper = true;
    m_magicX = 0;
    m_magicY = 0;

    getLocalBounds();

    m_initialized = true;

}

//=======================================================================
void RainbowText::reset() 
{
    m_initialized = false;
    m_initialized_colors = false;
    m_initialized_chars = false;
    m_chars.clear();
    m_colors.clear();
    m_magic_skipper = true;
    m_magicX = 0;
    m_magicY = 0;
}

//=======================================================================
sf::Color RainbowText::changeColor(const sf::Color& color, int delta)
{
    int colR = color.r;
    int colG = color.g;
    int colB = color.b;

    // Color changing logic
    if (color.r == 255 && color.g < 255 && color.b == 0) colG += delta;
    else if (color.r > 0 && color.g == 255 && color.b == 0) colR -= delta;
    else if (color.r == 0 && color.g == 255 && color.b < 255) colB += delta;
    else if (color.r == 0 && color.g > 0 && color.b == 255) colG -= delta;
    else if (color.r < 255 && color.g == 0 && color.b == 255) colR += delta;
    else if (color.r == 255 && color.g == 0 && color.b > 0) colB -= delta;

    colR = std::clamp(colR, 0, 255);
    colG = std::clamp(colG, 0, 255);
    colB = std::clamp(colB, 0, 255);

    return sf::Color(colR, colG, colB, color.a);
}

//=======================================================================
void RainbowText::logic() //tell me what this logic does
{
    if (!m_initialized) 
    {
        return;
    }

    m_char_num = this->getString().getSize();
    if (m_comp.getString() != this->getString())
    {
        m_chars.clear();
        m_chars.reserve(m_char_num);
        for (int i = 0; i < m_char_num; ++i)
        {
            m_chars.emplace_back(this->getString().substring(i, 1), DefaultFont::getFont(), this->getCharacterSize());
        }
        m_comp = *this;
        m_color_num = ((m_char_num + 17) / 18) * 18;

    }

    for (int i = 0; i < m_char_num; ++i)
    {
        m_chars[i].setScale(this->getScale());
        m_chars[i].setRotation(this->getRotation());
        m_chars[i].setPosition(this->findCharacterPos(i));
        m_chars[i].setOutlineColor(this->getOutlineColor());
        m_chars[i].setOutlineThickness(this->getOutlineThickness());
    }

    if (!m_initialized_colors)
    {
        m_colors.reserve(m_color_num);
        m_colors.emplace_back(255, 0, 0, 255);
        for (int i = 1; i < m_color_num; ++i)
        {
            m_colors.emplace_back(changeColor(m_colors[i - 1], 85));
        }
        m_initialized_colors = true;
    }

    int colorIndex;
    if (m_magic_skipper)
    {
        for (int i = 0; i < m_char_num; ++i)
        {
            colorIndex = (m_magicX + i) % m_color_num;
            m_chars[i].setFillColor(m_colors[colorIndex]);
        }
        m_magicX = (m_magicX + 1) % m_color_num;
        m_magic_skipper = false;
    }
    else {
        m_magic_skipper = true;
    }

}

//=======================================================================
void RainbowText::setLayer(Layer& _layer)
{
    m_layer = &_layer;
}

//=======================================================================
void RainbowText::render(sf::RenderWindow& window)
{
    if (m_visible && m_layer)
    {
        for (auto& ch : m_chars)
        {
            m_layer->render(window, ch);
        }
    }
}

//=======================================================================
void RainbowText::scale(const sf::Vector2f& size)
{
    this->setScale(size);
}

//=======================================================================
bool RainbowText::isClicked(const sf::Vector2f mousePos) const
{
    return this->getGlobalBounds().contains(mousePos);
}

//=======================================================================
bool RainbowText::isHoveredOn(const sf::Vector2f& mousePos) const
{
    return this->getGlobalBounds().contains(mousePos);
}

