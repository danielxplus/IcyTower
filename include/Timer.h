#pragma once
#include "Object.h"
#include "Factory.h"
#include "Game.h"

class Timer : public Object
{
public:
	using Object::Object;

	virtual void setBasic(float& x, float& y, Layer& layer) override;

	virtual void init() override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void reset() override;
	virtual void logic() override;

	virtual float getPosX() override { return 0; };
	virtual float getPosY() override { return 0; };
	virtual float getStartX() override { return 0; };
	virtual float getEndX() override { return 0; };

	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual bool collison(sf::Sprite sprite, float m_posX) override { return false; };
	virtual void gameOverLogic() override {};

	bool getstarted();
	
	static bool started;

private:

	sf::Clock m_clock;
	sf::Time m_time;

	int m_levels[7] = { 0,1,2,4,6,9,11 };

	int m_cur_level = 0;

	bool berserk = false,
		shaking = false,
		hurrying = false;

	sf::Sprite m_clock_sprite,
		m_clock_handle_sprite;

	sf::Music m_ring_buffer,
		m_timer_buffer;

	enum Sprites
	{
	Clock, HurryUpText
	};
};

void setStarted(bool start);