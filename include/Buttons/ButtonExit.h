#pragma once
#include "Button.h"
class ButtonExit : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;
private:
};