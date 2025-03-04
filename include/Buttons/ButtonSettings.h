#pragma once
#include "Button.h"
#include "Menu.h"
#include "ButtonDifficulty.h"
#include "ButtonChar.h"
#include "ButtonSound.h"
#include "ButtonReturn.h"

class ButtonSettings : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;

private:
	void addButtons(Menu &menu,Layer & layer);
	void loadChar();


	sf::Sprite m_background;
	Assets m_assets = m_assets.getInstance();

	sf::Texture m_char_texture;
	sf::Sprite m_char_sprite;
	
};