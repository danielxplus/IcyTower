#pragma once
#include "Button.h"

class ButtonInstructions : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;

private:
	void initText(Layer &layer);
	void logicText();
	void drawText(sf::RenderWindow& window);

	sf::Sprite m_background;
	Assets m_assets = m_assets.getInstance();
	RainbowText text_instruction;
};