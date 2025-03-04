#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class EyeCandy
{
public:
	EyeCandy(const float& posX, const float& posY);
	EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir);
	EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed);

	sf::ConvexShape& getDrawable();
	float getPosY();
	void reset();
	void logic();

private:
	void changeColor();
	void createStarShape();

	int m_color_change_index;
	float m_gravity;
	int m_start_posX;
	int m_start_posY;
	float m_start_speedX;
	float m_start_speedY;
	float m_speedX;
	float m_speedY;
	sf::ConvexShape m_candy;
};
