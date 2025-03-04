#include "Buttons/ButtonExit.h"

void ButtonExit::action(sf::RenderWindow& window, Layer& layer)
{
	window.close();
}
