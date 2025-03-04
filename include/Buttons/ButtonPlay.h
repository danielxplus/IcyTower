#pragma once
#include "Button.h"
#include "Game.h"

class ButtonPlay : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;
private:
};