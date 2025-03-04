#pragma once
#include "Button.h"
class ButtonReturn : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;
private:
};