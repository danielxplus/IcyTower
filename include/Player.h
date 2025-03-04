#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "Game.h"
#include "Menu.h"
#include "Camera.h"
#include "Animation.h"
#include "Timer.h"
#include "EyeCandyEngine.h"
#include "PitchedSound.h"
#include "Consts.h"
#include "StatePlayerAnimation.h"
#include "StatePlayerMovement.h"

class Player
{
public:	
	Player();
	void init();
	void logic();
	void render(sf::RenderWindow& window);
	void reset();
	void stopBGM();
	sf::Drawable& getDrawable();

	void setLayer(Layer& layer) { curLayer = layer; };
	int checkBoundaries();

	EyeCandyEngine ece_milestone;

	bool gift_plat_on;
	bool gift_shield_on;
	bool gift_gravity_on;

	// for State pattern
	void setStateAnimation(std::unique_ptr<StatePlayerAnimation> state);
	void setStateMovement(std::unique_ptr<StatePlayerMovement> state);

	// in public because State needs access:

	void move();
	std::unique_ptr <Object>* m_curr_platform;

	static PitchedSound m_player_sound;
	sf::Sprite m_player_sprite;

	short m_side;
	short m_jump_strength;

	bool m_accelerating;

	float m_speedX;
	float m_speedY;
	float delta_speed;

	float m_pos_X;
	float m_pos_Y;

protected:
	Layer& curLayer;

private:
	
	void collide();
	void checkPlatCollision();
	void milestoneReward();

	void animationAndSound();
	void jump();

	void checkMilestone();
	void checkTimer();
	void checkMove();
	void checkJump();
	void checkCam();
	void checkCandy();
	void checkGameOver();
	void initializePosition();
	
	void playSound(const sf::SoundBuffer& sound);

	bool is_on_ground;

	bool m_touched_enemy;

	EyeCandyEngine m_ec_combo;

	int m_curr_level;
	int m_level_milestone;
	bool milestone_mode;

	sf::Texture m_player_texture;

	sf::SoundBuffer sound_jump_low;
	sf::SoundBuffer sound_jump_mid;
	sf::SoundBuffer sound_jump_high;
	sf::SoundBuffer sound_edge;
	sf::SoundBuffer sound_falling;

	sf::SoundBuffer m_sound_milestone;
	sf::Sound m_player_sound_milestone;

	std::unique_ptr<StatePlayerAnimation> m_animation_state;
	std::unique_ptr<StatePlayerMovement> m_movement_state;
};
