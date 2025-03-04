#pragma once
#include "Camera.h"
#include "Factory.h"
#include "Consts.h"
#include "Player.h"
#include "Score.h"
#include "Timer.h"

class Game {
public:
	Game(sf::RenderWindow& window) ;

	bool run();
	void init();

	void objectLogic();
	void render(sf::RenderWindow& window);

	void handleEvent(const sf::Event& event);
	void handleLoadingState();
	void handleInGameState();
	void handleResettingState();
	void handleGameOverState();
	void handleGoToMenu();
	void checkGameOver();
	void setState(ENUM_GAME_STATES state);
	void reset();
	ENUM_GAME_STATES getState();

	static std::vector<std::unique_ptr<Object>> m_platforms;
	static Layer m_Platform;
	static ENUM_GAME_STATES game_state;
	static Layer m_HUD;

	static bool is_game_over;

private:
	std::vector<std::unique_ptr<Object>> m_objects;

protected:
	sf::RenderWindow &game_window;	
};