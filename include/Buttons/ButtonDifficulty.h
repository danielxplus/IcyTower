#pragma once
#include "Button.h"
#include "Menu.h"
class ButtonDifficulty : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;
private:
};