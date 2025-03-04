#pragma once
#include "Button.h"
#include "DefaultFont.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include "RainbowText.h"

class ButtonLeaderboard : public Button
{
public:
	using Button::Button;
	virtual void action(sf::RenderWindow& window, Layer& layer) override;

private:
	void initText(Layer& layer);
	void logicText();
	void drawText(sf::RenderWindow& window);
	void updateScoreText();

	int m_top_score_array[3];

	sf::Sprite m_background;
	Assets m_assets = m_assets.getInstance();

	RainbowText m_return;
	RainbowText m_text_title;
	RainbowText m_text_scores[3] =
	{
		RainbowText("Highest Score - " + std::to_string(m_top_score_array[0]), DefaultFont::getFont(), 60),
		RainbowText("Second Highest Score - " + std::to_string(m_top_score_array[1]), DefaultFont::getFont(), 60),
		RainbowText("Third Highest Score - " + std::to_string(m_top_score_array[2]), DefaultFont::getFont(), 60)
	};

	RainbowText m_text_play_first;

};