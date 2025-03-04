#include "EyeCandy.h"

// combo mode
EyeCandy::EyeCandy(const float& posX, const float& posY)
{
	m_color_change_index = 5;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(-10, 10);
	std::uniform_real_distribution<> randDir(-2, 2);
	std::uniform_real_distribution<> randGrav(0.075, 0.15);
	m_start_posX = posX + randPos(rand);
	m_start_posY = posY + randPos(rand);
	m_start_speedX = randDir(rand);
	m_start_speedY = -2;
	m_speedX = m_start_speedX;
	m_speedY = m_start_speedY;
	m_gravity = randGrav(rand);

	createStarShape();
}

// combo *reward*
EyeCandy::EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir)
{
	m_color_change_index = 5;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(_randPos * -1, _randPos);
	std::uniform_real_distribution<> randDir(_randDir * -1, _randDir);
	std::uniform_real_distribution<> randGrav(0.075, 0.15);
	m_start_posX = posX + randPos(rand);
	m_start_posY = posY;
	m_start_speedX = randDir(rand);
	m_start_speedY = -2;
	m_speedX = m_start_speedX;
	m_speedY = m_start_speedY;
	m_gravity = randGrav(rand);

	createStarShape();
}

// milestone
EyeCandy::EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed)
{
	m_color_change_index = 5;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(_randPos * -1, _randPos);
	std::uniform_real_distribution<> randDir(_randDir * -1, _randDir);
	std::uniform_real_distribution<> randGrav(0.075, 0.15);
	m_start_posX = posX + randPos(rand);
	m_start_posY = posY;
	m_start_speedX = randDir(rand);
	m_start_speedY = _ySpeed;
	m_speedX = m_start_speedX;
	m_speedY = m_start_speedY;
	m_gravity = randGrav(rand);

	createStarShape();
}

sf::ConvexShape& EyeCandy::getDrawable()
{
	return m_candy;
}

float EyeCandy::getPosY()
{
	return m_candy.getPosition().y;
}

void EyeCandy::reset()
{
	m_candy.setPosition(m_start_posX, m_start_posY);
	m_speedX = m_start_speedX;
	m_speedY = m_start_speedY;
}

void EyeCandy::logic()
{
	changeColor();  // Update the color every frame

	// Move the candy based on speed
	m_candy.move(m_speedX, m_speedY);

	// Increase the falling speed (gravity) faster
	if (m_speedY < 8)  // Cap the falling speed at 8 for this example
	{
		m_speedY += m_gravity * 2;  // Multiply gravity to make the falling speed faster
	}

	// Adjust horizontal speed (optional, for drift effect)
	if (m_speedX < -0.5)
	{
		m_speedX += 0.02;
	}
	else if (m_speedX > 0.5)
	{
		m_speedX -= 0.02;
	}
}

void EyeCandy::changeColor()
{
    // Generate random color components
    std::random_device rd;
    std::mt19937 rand(rd());
    std::uniform_int_distribution<int> randColor(0, 255);  // RGB values between 0 and 255

    // Create a random color for each frame
	sf::Color random_color(randColor(rand), randColor(rand), randColor(rand), 255);  // Fully opaque

    // Apply the random color to the star
    m_candy.setFillColor(random_color);
}

void EyeCandy::createStarShape()
{
	m_candy.setPointCount(10);
	m_candy.setPoint(0, sf::Vector2f(5, 0));
	m_candy.setPoint(1, sf::Vector2f(6, 3));
	m_candy.setPoint(2, sf::Vector2f(10, 3));
	m_candy.setPoint(3, sf::Vector2f(8, 6));
	m_candy.setPoint(4, sf::Vector2f(9, 9));
	m_candy.setPoint(5, sf::Vector2f(5, 8));
	m_candy.setPoint(6, sf::Vector2f(1, 9));
	m_candy.setPoint(7, sf::Vector2f(2, 6));
	m_candy.setPoint(8, sf::Vector2f(0, 3));
	m_candy.setPoint(9, sf::Vector2f(4, 3));

	m_candy.setOrigin(5, 4);
	m_candy.setPosition(m_start_posX, m_start_posY);
}
