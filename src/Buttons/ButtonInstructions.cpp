#include "Buttons/ButtonInstructions.h"
#include <iostream>

//=======================================================================
void ButtonInstructions::action(sf::RenderWindow& window, Layer& layer)
{
	bool back_to_menu = false;
	window.clear();
	initText(layer);
	this->m_background.setTexture(m_assets.getTexture("menu_bg"));
	layer.logic();

	while (window.isOpen()&&!back_to_menu)
	{

		sf::View menu_view = window.getView();
		layer.setView(menu_view);
		logicText();
		window.clear();
		window.draw(this->m_background);
		drawText(window);
	
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
//=======================================================================
void ButtonInstructions::initText(Layer &layer)
{
	text_instruction.setPosition(const_menu_title_pos);
	text_instruction.setFont(DefaultFont::getFont());
	text_instruction.setString("Instructions:\n\nhelp the \character climb the tower!\nthe faster you run, the higher you jump.\
	\nuse the keyboard to control the player.\nmake double or triple jumps!\nuse gifts to enjoy different perks.\n\n\
			press ESC to return to menu.");
	text_instruction.setOutlineThickness(const_text_outline_large);
	text_instruction.setCharacterSize(50);
	text_instruction.setLayer(layer);
	text_instruction.init();
}
//=======================================================================
void ButtonInstructions::logicText()
{
	text_instruction.logic();
}
//=======================================================================
void ButtonInstructions::drawText(sf::RenderWindow& window)
{
	text_instruction.render(window);
}