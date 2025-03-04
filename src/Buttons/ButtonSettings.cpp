#include "Buttons/ButtonSettings.h"
#include "iostream"

void ButtonSettings::action(sf::RenderWindow& window, Layer& layer)
{
	sf::Vector2f mousePos;

	bool m_back_to_menu = false;

	Menu sub_menu(layer);
	addButtons(sub_menu, layer);
	sub_menu.init();
	layer.logic();
	this->m_background.setTexture(m_assets.getTexture("menu_bg"));

	while (window.isOpen() && !m_back_to_menu)
	{
		sf::View menu_view = window.getView();
		layer.setView(menu_view);
		sub_menu.logic();
		loadChar();

		window.clear();

		window.draw(this->m_background);
		window.draw(m_char_sprite);
		sub_menu.draw(window);


		window.display();
		for (auto event = sf::Event{}; window.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:

				window.close();
				break;

			case sf::Event::MouseButtonReleased:

				mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				sub_menu.handleClick(mousePos, window);
				break;

			case sf::Event::MouseMoved:

				sf::Event::MouseMoveEvent mouse = event.mouseMove;
				mousePos = window.mapPixelToCoords({ mouse.x, mouse.y });
				sub_menu.handleHoverEffects(mousePos);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_back_to_menu = true;
					break;
				}
			} // switch

		}

	}
}


void ButtonSettings::addButtons(Menu& menu, Layer& layer)
{
	menu.addButton((std::make_unique<ButtonChar>(const_button_char_pos, "CHANGE CHARACTER: ", layer)), "char_button");
	menu.addButton((std::make_unique<ButtonDifficulty>(const_button_lead_pos, "DIFFICULTY: NORMAL", layer)), "difficulty_button");
	if(Menu::bool_sound)
	{
		menu.addButton((std::make_unique<ButtonSound>(const_button_sound_pos, "SOUND: ON", layer)), "sound_button");
	}
	else
	{
		menu.addButton((std::make_unique<ButtonSound>(const_button_sound_pos, "SOUND: OFF", layer)), "sound_button");
	}
	menu.addButton((std::make_unique<ButtonReturn>(const_button_return_pos, "press ESC to return to menu. ", layer)), "return_button");

}

void ButtonSettings::loadChar()
{
	Menu::player_data.player_bgm.openFromFile("Sounds\\harold_bgm.mp3");
	switch (Menu::player)
	{
	case harold:
		Menu::player_data.bmp_file = m_assets.getImage("harold");
		Menu::player_data.sound_hello = m_assets.getSound("hello");
		Menu::player_data.sound_edge = m_assets.getSound("edge");
		Menu::player_data.sound_jump_falling = m_assets.getSound("falling");
		Menu::player_data.sound_jump_high = m_assets.getSound("jump_high");
		Menu::player_data.sound_jump_mid = m_assets.getSound("jump_mid");
		Menu::player_data.sound_jump_low = m_assets.getSound("jump_low");
		Menu::player_data.player_bgm.openFromFile("Sounds\\harold_bgm.mp3");
		break;

	case kirby:
		Menu::player_data.bmp_file = m_assets.getImage("kirby");
		Menu::player_data.sound_hello = m_assets.getSound("kirby_hello");
		Menu::player_data.sound_edge = sf::SoundBuffer();
		Menu::player_data.sound_jump_falling = m_assets.getSound("kirby_death");
		Menu::player_data.sound_jump_high = sf::SoundBuffer();
		Menu::player_data.sound_jump_mid = sf::SoundBuffer();
		Menu::player_data.sound_jump_low = sf::SoundBuffer();
		Menu::player_data.player_bgm.openFromFile("Sounds\\KBgm.mp3");
		Menu::player_data.player_bgm.setVolume(7);
		break;

	case dave:
		Menu::player_data.bmp_file = m_assets.getImage("dave");
		Menu::player_data.sound_hello = m_assets.getSound("cmonyo");
		Menu::player_data.sound_edge = m_assets.getSound("watchit");
		Menu::player_data.sound_jump_falling = m_assets.getSound("diggin");
		Menu::player_data.sound_jump_high = m_assets.getSound("stayinalive");
		Menu::player_data.sound_jump_mid = m_assets.getSound("ahey");
		Menu::player_data.sound_jump_low = m_assets.getSound("ho");
		Menu::player_data.player_bgm.openFromFile("Sounds\\disco_bgm.mp3");
		Menu::player_data.player_bgm.setVolume(7);
		break;

	}
	Menu::player_data.bmp_file.createMaskFromColor(sf::Color(153, 20, 145, 255));

	m_char_texture.loadFromImage(Menu::player_data.bmp_file, Animation::animation_idle1);
	m_char_sprite.setTexture(m_char_texture);
	m_char_sprite.setPosition(const_char_pos);
	m_char_sprite.setScale(2,2);
}


