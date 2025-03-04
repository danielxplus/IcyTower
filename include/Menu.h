#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "Buttons/Button.h"
#include <unordered_map>

class Menu
{
public:

	static bool bool_sound;
	static sf::Music menu_bgm;
	static ENUM_PLAYER_PRESET player;
	static ENUM_DIFFICULTY difficulty;
	static playerData player_data;
	
	Menu(Layer& currLayer);
	void init();
	void logic();
	
	void handleHoverEffects(const sf::Vector2f& mouse_pos_f);
	void handleClick(const sf::Vector2f& mouse_pos_f, sf::RenderWindow& window) const;
	void draw(sf::RenderWindow& window) const;
	void addButton(std::unique_ptr<Button> button, std::string name);

private:
	std::unordered_map<std::string, std::unique_ptr<Button>> m_buttons;
	Layer &m_menu_layer;

};


