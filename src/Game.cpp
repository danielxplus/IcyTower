#include "Game.h"

Layer m_Background(3);
Layer Game::m_Platform(2);
Layer m_Wall(3);
Layer Game::m_HUD(2);

std::vector<std::unique_ptr<Object>> Game::m_platforms;

ENUM_GAME_STATES Game::game_state;

Player m_player;

bool Game::is_game_over;

Game::Game(sf::RenderWindow& window)
	:game_window(window)
{
	m_objects.emplace_back(Factory::createInitialized("Background", 25, -120, m_Background));
	m_objects.emplace_back(Factory::createInitialized("PlatformEngine", 0, 0, m_Platform));
	m_objects.emplace_back(Factory::createInitialized("WallRight", 570, -120, m_Background));
	m_objects.emplace_back(Factory::createInitialized("WallLeft", 0, -120, m_Background));
	m_objects.emplace_back(Factory::createInitialized("Score", 0, 0, m_HUD));
	m_objects.emplace_back(Factory::createInitialized("Timer", 0, 0, m_HUD));

	//creation of the platforms
	for (int i = 1; i < 8; i++)
	{
		m_platforms.emplace_back(Factory::createInitialized("Platform", i, 0, m_Platform));
	}

	setState(Loading);

	m_player.setLayer(m_platforms[0].get()->m_layer);
}

bool Game::run()
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	unsigned int window_width = desktopMode.width / 1.875;
	unsigned int window_height = desktopMode.height / 1.875;

	game_window.create(sf::VideoMode(window_width, window_height), "Icy Tower", sf::Style::Close);

	sf::Image game_icon;
	game_icon.loadFromFile("icon.png");
	game_window.setIcon(game_icon.getSize().x + 0.2, game_icon.getSize().y, game_icon.getPixelsPtr());

	while (game_window.isOpen())
	{
		sf::Event event;
		if (game_window.pollEvent(event))
		{
			handleEvent(event);
		}
		if (game_state == InGame)
		{
			handleInGameState();
		}
		else if (game_state == GameOver)
		{
			handleGameOverState();
		}
		else if (game_state == Resetting)
		{
			handleResettingState();
		}
		else if (game_state == Loading)
		{
			handleLoadingState();
		}
		else if (game_state == ReturnToMenu)
		{
			handleGoToMenu();

			return true;
		}
	}
}

void Game::init()
{
	for (auto& ptr : m_objects)
	{
		ptr->init();
	}

}

void Game::objectLogic()
{
	for (auto& ptr : m_objects)
	{
		ptr->logic();
	}
}

void Game::render(sf::RenderWindow& window)
{
	for (auto& ptr : m_objects)
	{
		ptr->render(window);
	}
	m_player.render(window);
}

void Game::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		m_player.stopBGM();
		handleGoToMenu();
		game_window.close();
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			reset();
			m_player.stopBGM();
			setState(ReturnToMenu);
		}
		else if (event.key.code == sf::Keyboard::Enter && game_state == GameOver)
		{
			setState(Resetting);
			handleResettingState();
		}
	}
}

void Game::handleLoadingState()
{
	game_window.setFramerateLimit(100);
	game_window.setKeyRepeatEnabled(false);
	init();
	game_window.display();
	m_player.init();
	setState(InGame);
}

void Game::handleInGameState()
{
	game_window.setView(m_Platform.view);
	game_window.clear();

	objectLogic();
	m_player.logic();
	render(game_window);
	m_player.render(game_window);
	checkGameOver();
	game_window.display();
}

void Game::reset()
{
	for (auto& ptr : m_objects)
	{
		ptr->reset();
	}

	m_Platform.reset();
	m_HUD.reset();
	m_player.reset();

	is_game_over = false;
}

void Game::handleResettingState()
{
	reset();
	setState(Loading);
}

void Game::handleGameOverState()
{
	game_window.setView(m_Platform.view);
	game_window.clear();

	for (auto& ptr : m_objects)
	{
		ptr->gameOverLogic();
	}

	m_player.logic();
	render(game_window);
	m_player.render(game_window);

	game_window.display();
}

void Game::handleGoToMenu()
{
	for (auto& ptr : m_objects)
	{
		ptr.release();
	}

	for (auto& ptr : m_platforms)
	{
		ptr.release();
	}

	m_objects.clear();
	m_platforms.clear();
}

void Game::checkGameOver()
{

	if (is_game_over)
	{
		setState(GameOver);
	}
}

void Game::setState(ENUM_GAME_STATES state)
{
	game_state = state;
}

ENUM_GAME_STATES Game::getState()
{
	return game_state;
}