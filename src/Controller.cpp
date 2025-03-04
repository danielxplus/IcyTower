#include "Controller.h"

//=======================================================================
Controller::Controller()
	:m_menu(menu_layer)
{

	DefaultFont::init();
	this->m_bgImge.setTexture(m_assets.getTexture("menu_bg"));
}

//=======================================================================
void Controller::addButtons()
{
	this->m_menu.addButton((std::make_unique<ButtonPlay>(const_button_play_pos, "Play", menu_layer)), "Play_button");
	this->m_menu.addButton((std::make_unique<ButtonLeaderboard>(const_button_lead_pos, "Leaderboard", menu_layer)), "Leaderboard_button");
	this->m_menu.addButton((std::make_unique<ButtonInstructions>(const_button_instruc_pos, "Instructions", menu_layer)), "Instructions_button");
	this->m_menu.addButton((std::make_unique<ButtonSettings>(const_button_settings_pos, "Settings", menu_layer)), "Settings_button");
	this->m_menu.addButton((std::make_unique<ButtonExit>(const_button_exit_pos, "Exit", menu_layer)), "Exit_button");
}

//=======================================================================
void Controller::run()
{
	// Basic init
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	unsigned int window_width = desktopMode.width / 1.875;
	unsigned int window_height = desktopMode.height / 1.875;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Icy Tower", sf::Style::Close);

	sf::Image game_icon;
	game_icon.loadFromFile("icon.png");
	window.setIcon(game_icon.getSize().x + 0.2, game_icon.getSize().y, game_icon.getPixelsPtr());

	sf::Vector2f mousePos;

	addButtons();
	m_menu.init();

	initDefaultCharSettings();

	Menu::menu_bgm.openFromFile("Sounds\\bgm.mp3");
	Menu::menu_bgm.setLoop(true);
	Menu::menu_bgm.setVolume(5);
	Menu::menu_bgm.play();
	
	menu_layer.logic();

	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		sf::View menu_view = window.getView();
		menu_layer.setView(menu_view);
		m_menu.logic();
		
		window.clear();

		window.draw(this->m_bgImge);
		m_menu.draw(window);


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
				m_menu.handleClick(mousePos, window);
				break;

			case sf::Event::MouseMoved:

				sf::Event::MouseMoveEvent mouse = event.mouseMove;
				mousePos = window.mapPixelToCoords({ mouse.x, mouse.y });
				m_menu.handleHoverEffects(mousePos);
			}
		}

	}

}

//=======================================================================
void Controller::initDefaultCharSettings()
{
	// used to init default settings for character (sound, sprite) to not rely on the user going into settings.
	Menu::player_data.bmp_file = m_assets.getImage("harold");
	Menu::player_data.sound_hello = m_assets.getSound("hello");
	Menu::player_data.sound_edge = m_assets.getSound("edge");
	Menu::player_data.sound_jump_falling = m_assets.getSound("falling");
	Menu::player_data.sound_jump_high = m_assets.getSound("jump_high");
	Menu::player_data.sound_jump_mid = m_assets.getSound("jump_mid");
	Menu::player_data.sound_jump_low = m_assets.getSound("jump_low");
	Menu::player_data.player_bgm.openFromFile("Sounds\\harold_bgm.mp3");
	Menu::player_data.bmp_file.createMaskFromColor(sf::Color(153, 20, 145, 255));

}