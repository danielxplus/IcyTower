#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Assets.h"
#include "Buttons/Button.h"
#include "Buttons/ButtonExit.h"
#include "Buttons/ButtonInstructions.h"
#include "Buttons/ButtonPlay.h"
#include "Buttons/ButtonSettings.h"
#include "Buttons/ButtonLeaderboard.h"
#include <memory>

class Controller
{
public:
	Controller();
	~Controller() = default;
	
	void addButtons();
	void initDefaultCharSettings();
	void run();

private:
	Assets m_assets = m_assets.getInstance();
	sf::Sprite m_bgImge;
	Menu m_menu;
	
	Layer menu_layer;
};
