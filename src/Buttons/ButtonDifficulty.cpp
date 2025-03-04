#include "Buttons/ButtonDifficulty.h"

void ButtonDifficulty::action(sf::RenderWindow& window, Layer& layer)
{
	switch (Menu::difficulty)
	{
	case easy:
		this->setText("DIFFICULTY: NORMAL");
		Menu::difficulty = normal;
		break;


	case normal:
		this->setText("DIFFICULTY: HARD");
		Menu::difficulty = hard;
		break;

	case hard:
		this->setText("DIFFICULTY: EASY");
		Menu::difficulty = easy;
		break;

	}
}