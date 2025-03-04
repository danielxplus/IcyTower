#include "Buttons/ButtonLeaderboard.h"

void ButtonLeaderboard::action(sf::RenderWindow& window, Layer& layer)
{
	bool back_to_menu = false;
	window.clear();
	initText(layer);
	this->m_background.setTexture(m_assets.getTexture("menu_bg"));
	layer.logic();

	while (window.isOpen() && !back_to_menu)
	{
		sf::View menu_view = window.getView();
		layer.setView(menu_view);
		logicText();
		window.clear();
		window.draw(this->m_background);
		drawText(window);

		updateScoreText();

		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:

				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					back_to_menu = true;
					break;
				}

			}

		}
	}
}

void ButtonLeaderboard::initText(Layer& layer)
{
	m_text_title.setPosition(const_menu_title_pos);
	m_text_title.setFont(DefaultFont::getFont());
	m_text_title.setString("TOP SCORES:");
	m_text_title.setCharacterSize(const_text_menu_size);
	m_text_title.setOutlineThickness(const_text_outline_large);
	m_text_title.setLayer(layer);
	m_text_title.init();

	m_text_play_first.setPosition(const_menu_title_pos.x, const_menu_title_pos.y + 150);
	m_text_play_first.setFont(DefaultFont::getFont());
	m_text_play_first.setString("No play history! \n Please play and come back.");
	m_text_play_first.setCharacterSize(const_text_menu_size);
	m_text_play_first.setOutlineThickness(const_text_outline_large);
	m_text_play_first.setLayer(layer);
	m_text_play_first.init();

	for (int i = 0; i < 3; i++)
	{
		m_text_scores[i].setPosition(const_menu_title_pos.x, const_menu_title_pos.y + 150 + (i * 100));
		m_text_scores[i].setCharacterSize(const_text_menu_size);
		m_text_scores[i].setOutlineThickness(const_text_outline_large);
		m_text_scores[i].setLayer(layer);
		m_text_scores[i].init();
	}

	m_return.setPosition(const_button_return_pos);
	m_return.setFont(DefaultFont::getFont());
	m_return.setString("Press ESC to return to menu");
	m_return.setCharacterSize(const_text_menu_size);
	m_return.setOutlineThickness(const_text_outline_large);
	m_return.setLayer(layer);
	m_return.init();

}

void ButtonLeaderboard::logicText()
{
	m_text_title.logic();
	m_text_play_first.logic();
	m_return.logic();
}

void ButtonLeaderboard::drawText(sf::RenderWindow& window)
{
	m_text_title.render(window);
	m_text_play_first.render(window);
	m_return.render(window);

	for (int i = 0; i < 3; ++i)
	{
		m_text_scores[i].render(window);
	}
}

void ButtonLeaderboard::updateScoreText()
{
	std::ifstream infile("topscores.txt");

	// Check if the file is empty
	if (infile.peek() == std::ifstream::traits_type::eof())
	{
		m_text_play_first.setVisible(true); // Assuming you have a setVisible method
		for (int i = 0; i < 3; ++i)
		{
			m_text_scores[i].setVisible(false); // Hide score texts
		}
	}
	else
	{
		m_text_play_first.setVisible(false); // Hide the "play first" message

		for (int i = 0; i < 3; ++i)
		{
			infile >> m_top_score_array[i];
		}

		m_text_scores[0].setString("Highest Score - " + std::to_string(m_top_score_array[0]));
		m_text_scores[1].setString("Second Highest Score - " + std::to_string(m_top_score_array[1]));
		m_text_scores[2].setString("Third Highest Score - " + std::to_string(m_top_score_array[2]));

		// Show the score texts
		for (int i = 0; i < 3; ++i)
		{
			m_text_scores[i].setVisible(true);
			m_text_scores[i].logic();
		}
	}
}
