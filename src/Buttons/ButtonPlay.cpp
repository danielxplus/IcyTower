#include "Buttons/ButtonPlay.h"

void ButtonPlay::action(sf::RenderWindow& window, Layer& layer)
{
	Menu::menu_bgm.stop();
	sf::View menu_view = window.getView();
	Game g(window);
	g.run();

	window.setView(menu_view);
	if (Menu::bool_sound)
	{
		Menu::menu_bgm.play();
	}
}