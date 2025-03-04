#include "Buttons/ButtonSound.h"

void ButtonSound::action(sf::RenderWindow& window, Layer& layer)
{
	if (Menu::bool_sound)
	{
		this->setText("SOUND: OFF");
		Menu::bool_sound = false;
		Menu::menu_bgm.stop();
	}
	else
	{
		this->setText("SOUND: ON");
		Menu::bool_sound = true;
		Menu::menu_bgm.play();
	}
}