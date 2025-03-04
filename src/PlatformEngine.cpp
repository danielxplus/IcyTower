#include "PlatformEngine.h"

bool registerPlatformEngine = Factory::registerit("PlatformEngine", []() -> std::unique_ptr<Object> { return std::make_unique<PlatformEngine>(); });

void PlatformEngine::setBasic(float& x, float& y, Layer& layer)
{
	this->m_layer = layer;
}


void PlatformEngine::init()
{
	m_layer.cam_posY = 0;
	for (int i = 0; i < 7; i++)
	{
		Game::m_platforms[i]->init();
	}
}

void PlatformEngine::render(sf::RenderWindow& window)
{
	window.setView(m_layer.view);
	for (int i = 0; i < 7; i++)
	{
		Game::m_platforms[i]->render(window);
	}
}

void PlatformEngine::reset()
{
	m_layer.view.reset(sf::FloatRect(0, 0, 640, 480));
	m_layer.reset();
	m_layer.cam_posY = 0;
	index = 0;
	m_layer.step = m_layer.const_step;

	for (int i = 0; i < 7; i++)
	{
		Game::m_platforms[i]->reset();
	}
}

void PlatformEngine::logic()
{
	
	float camSpeed = Camera::getCamSpeed();
	m_layer.view.reset(sf::FloatRect(0, m_layer.cam_posY, 640, 480));
	
	m_layer.cam_posY -= const_cam_speed_delta * camSpeed * m_layer.speed_delta;
	m_layer.step -= camSpeed;
	Game::m_platforms[index]->logic();
	if (index < 6)
		index++;
	else index = 0;
}



