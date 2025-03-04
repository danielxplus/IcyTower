#include "EyeCandyEngine.h"

EyeCandyEngine::EyeCandyEngine()
{
	m_layer = nullptr;
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, int count)
{
	for (int i = 0; i < count; i++)
	{
		m_engine.push_back(EyeCandy(posX, posY));
	}
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, int count)
{
	for (int i = 0; i < count; i++)
	{
		m_engine.push_back(EyeCandy(posX, posY, _randPos, _randDir));
	}
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed, int count)
{
	for (int i = 0; i < count; i++)
	{
		m_engine.push_back(EyeCandy(posX, posY, _randPos, _randDir, _ySpeed));
	}
}

void EyeCandyEngine::resetCandy()
{
	for (EyeCandy& eye_candy : m_passive_engine)
	{
		eye_candy.reset();
	}
	m_engine = m_passive_engine;
	m_passive_engine.clear();
}

void EyeCandyEngine::logic()
{
	for (EyeCandy& eye_candy : m_engine)
	{
		eye_candy.logic();
	}
}

void EyeCandyEngine::render(sf::RenderWindow& window, bool _reset)
{
	for (int i = 0; i < m_engine.size(); i++)
	{
		EyeCandy& eye_candy = m_engine.at(i);

		// Draw each EyeCandy directly to the window
		window.draw(eye_candy.getDrawable());

		// Check if EyeCandy is off-screen
		if (eye_candy.getPosY() > window.getView().getCenter().y + 240 && m_engine.size() > 0)
		{
			// If _reset is true, move the EyeCandy to m_passive_engine
			if (_reset)
			{
				m_passive_engine.push_back(eye_candy);
			}
			// Remove the EyeCandy from m_engine
			m_engine.erase(m_engine.begin() + i);
			i--;  // Adjust index to avoid skipping the next EyeCandy
		}
	}
}

void EyeCandyEngine::setLayer(Layer& _layer)
{
	m_layer = &_layer;
}

int EyeCandyEngine::getCount()
{
	return m_engine.size();
}

void EyeCandyEngine::reset()
{
	m_engine.clear();
	m_passive_engine.clear();
}
