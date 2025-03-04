#include "Menu.h"

ENUM_DIFFICULTY Menu::difficulty;
ENUM_PLAYER_PRESET Menu::player;

playerData Menu::player_data;

bool Menu::bool_sound = true;
sf::Music Menu::menu_bgm;

//=======================================================================
Menu::Menu(Layer &currLayer)
	:m_menu_layer(currLayer)
{
}

//=======================================================================
void Menu::init()
{
	for (const auto& [name, btn] : this->m_buttons)
	{
		btn->initRainbow();
	}
}

//=======================================================================
void Menu::logic()
{
	for (const auto& [name, btn] : this->m_buttons)
	{
		btn->logicRainbow();
	}
}

//=======================================================================
void Menu::handleHoverEffects(const sf::Vector2f& mouse_pos_f)
{
	for (const auto& [name, btn] : this->m_buttons)
	{
		if (btn->isHovered(mouse_pos_f))
		{
			btn->scale(const_button_hover_size);
		}
		else
		{
			btn->scale(const_button_def_size);
		}
	}
}

//=======================================================================
void Menu::handleClick(const sf::Vector2f& mouse_pos_f, sf::RenderWindow& window) const
{
	for (const auto& [name, btn] : this->m_buttons)
	{
		if (btn->isClicked(mouse_pos_f))
		{
			btn->action(window,m_menu_layer); 
		}
	}
}

//=======================================================================
void Menu::draw(sf::RenderWindow& window) const
{
    for (const auto& [name, btn] : this->m_buttons)
    {
        btn->draw(window);
    }
}

//=======================================================================
void Menu::addButton(std::unique_ptr<Button> button, std::string name)
{
    m_buttons[name] = std::move(button);
}
