#include "Buttons/ButtonChar.h"
#include "Consts.h"

void ButtonChar::action(sf::RenderWindow& window, Layer& layer)
{
	switch (Menu::player) // cycle behaviour
	{
	case harold:
		Menu::player = dave;
		break;
	case dave:
		Menu::player = kirby;
		break;
	case kirby:
		Menu::player = harold;
		break;
	}
	
}

