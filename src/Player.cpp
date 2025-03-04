#include "Player.h"

#include "StateAnimations/StateIdle.h"
#include "StateAnimations/StateOnEdge.h"
#include "StateAnimations/StateChock.h"
#include "StateAnimations/StateWalking.h"
#include "StateAnimations/StateJumping.h"

#include "StateMovement/StateMovingLeft.h"
#include "StateMovement/StateMovingRight.h"
#include "StateMovement/StateNotMoving.h"

PitchedSound Player::m_player_sound;
bool text_mode;

Layer temp_layer;

Player::Player()
	:curLayer(temp_layer)
{
}

void Player::init()
{
	curLayer.cam_posY = 0;
	setStateAnimation(std::make_unique<StateIdle>());

	text_mode = false;
	if (Menu::bool_sound)
	{
		Menu::player_data.player_bgm.setLoop(true);
		Menu::player_data.player_bgm.setVolume(4);
		Menu::player_data.player_bgm.play();
	}

	m_player_texture.loadFromImage(Menu::player_data.bmp_file);
	m_player_sprite.setTexture(m_player_texture);

	initializePosition();

	reset();
}

void Player::reset()
{

	sf::View view;
	view.reset(sf::FloatRect(0, 0, 640, 480));
	curLayer.setView(view);

	is_on_ground = true;
	m_curr_platform = &Game::m_platforms[0];

	m_curr_level = 1;
	m_level_milestone = 50;
	milestone_mode = false;
	m_jump_strength = 0;
	m_speedX = 0;
	m_speedY = 0;
	m_accelerating = false;
	delta_speed = 0;
	m_side = 0;

	m_player_sprite.setOrigin(14, 35);
	initializePosition();
	m_player_sprite.setRotation(0);
	m_ec_combo.reset();
	ece_milestone.reset();
	ece_milestone.addCandy(320, -80*40, 320, 4, -9, 50);

	playSound(Menu::player_data.sound_hello);
}

void Player::logic()
{

	if (Game::game_state != Resetting)
	{
		checkJump();
		checkMove();
	}

	checkPlatCollision();
	checkTimer();
	checkCam();
	checkGameOver();
	checkCandy();
	checkMilestone();
	animationAndSound();
}

int Player::checkBoundaries()
{
	if (m_pos_X >= const_left_bound && m_pos_X <= const_right_bound)
	{
		return 0;
	}
	else if (m_pos_X < const_left_bound)
	{
		return const_left_bound;
	}
	else
	{
		return const_right_bound;
	}
}

void Player::milestoneReward()
{
	m_level_milestone += 50;
	milestone_mode = true;
}

void Player::checkMilestone()
{
	static int count_and_multiply = 1;
	if (ece_milestone.getCount() == 0)
	{
		int y_pos = -4000 * count_and_multiply;
		milestone_mode = false;
		ece_milestone.addCandy(320, -80*40 + y_pos, 320, 4, -9, 50);
		count_and_multiply++;
	}
	if (milestone_mode)
	{
		ece_milestone.logic();
	}
	
}

void Player::collide()
{
	if (m_touched_enemy)
	{
		return;
	}

	float dist = (m_jump_strength == 3) ? const_dist_between_platforms - 8 : const_dist_between_platforms;

	if (m_pos_Y > -const_dist_between_platforms * m_curr_level + const_player_start_pos_y + dist)
	{
		for (auto& platform : Game::m_platforms)
		{
			if (platform->getPosX() == m_curr_level &&
				m_pos_X >= platform->getStartX() - m_player_sprite.getTextureRect().width / 2 &&
				m_pos_X <= platform->getEndX() + m_player_sprite.getTextureRect().width / 2)

			{
				m_jump_strength = 0;
				m_speedY = 0;

				m_player_sprite.setOrigin(14, 35);
				m_player_sprite.setRotation(0);
				m_pos_Y = const_player_start_pos_y - const_dist_between_platforms * (m_curr_level - 1);

				is_on_ground = true;
				m_curr_platform = &platform;

				updateGlobalScore(m_curr_level); // updated score via Score class

				if (m_curr_level >= m_level_milestone)
				{
					milestoneReward();
				}
			}
		}
	}
}

void Player::checkPlatCollision()
{
	if (is_on_ground &&
		!(m_pos_X >= m_curr_platform->get()->getStartX() - m_player_sprite.getTextureRect().width / 2 &&
			m_pos_X <= m_curr_platform->get()->getEndX() + m_player_sprite.getTextureRect().width / 2))
	{
		m_jump_strength = 0;
		is_on_ground = false;
	}
}

void Player::move()
{

	if (!checkBoundaries())
	{
		if (m_accelerating && m_speedX < const_player_xspeed_max) //accelerate
		{
			m_speedX += delta_speed;
		}
		else if (m_speedX - delta_speed < 0) //stop
		{
			m_speedX = 0;
		}
		else m_speedX -= delta_speed;
		m_pos_X += m_side * m_speedX;
	}
	else
	{
		m_pos_X = checkBoundaries();
		m_side *= -1;
	}
}

void Player::jump()
{
	m_pos_Y += m_speedY;
	if (m_speedY < const_player_yspeed_max)
	{
		m_speedY += const_player_gravity;
	}
	if (m_speedY > 0.0f)
	{
		collide();
	}
}

void Player::checkJump()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		is_on_ground &&
		!m_touched_enemy)
	{
		is_on_ground = false;
		if (m_speedX > 5.9f)
		{
			m_speedY = m_speedX * -1 - 5.75;
			m_jump_strength = 3;
			m_pos_Y += -8;
			playSound(Menu::player_data.sound_jump_high);
		}
		else if (m_speedX > 3.9f)
		{
			m_speedY = m_speedX * -0.5 - 5.75;
			m_jump_strength = 2;
			playSound(Menu::player_data.sound_jump_mid);
		}
		else
		{
			m_speedY = -5.75;
			m_jump_strength = 1;
			playSound(Menu::player_data.sound_jump_low);
		}
	}
	else if (!is_on_ground)
	{
		jump();
	}
	m_curr_level = (m_pos_Y - const_player_start_pos_y) / const_dist_between_platforms * -1 + 1; //updated on every frame, brains of collision detection
}

void Player::animationAndSound()
{
	if (is_on_ground)
	{
		if (m_speedX != 0)
		{
			setStateAnimation(std::make_unique<StateWalking>());
		}
		else if (m_pos_X <= m_curr_platform->get()->getStartX() + 10 ||
			m_pos_X >= m_curr_platform->get()->getEndX() - 10)
		{
			setStateAnimation(std::make_unique<StateOnEdge>());
		}
		else if (Camera::getCamLevel() > 0 && m_pos_Y > curLayer.getViewCenter() + const_chock_anim_trigger_bound)
		{
			setStateAnimation(std::make_unique<StateChock>());
		}
	}
	else
	{
		setStateAnimation(std::make_unique<StateJumping>());
	}

	// Call handle on the current state
	if (m_animation_state)
	{
		m_animation_state->handle(*this);
	}

	setStateAnimation(std::make_unique<StateIdle>()); // default animation
}

void Player::checkMove()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		setStateMovement(std::make_unique<StateMovingLeft>());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setStateMovement(std::make_unique<StateMovingRight>());
	}
	else
	{
		setStateMovement(std::make_unique<StateNotMoving>());
	}

	if (m_movement_state)
	{
		m_movement_state->handle(*this);
	}

}

void Player::setStateAnimation(std::unique_ptr<StatePlayerAnimation> state)
{
	m_animation_state = std::move(state);
}

void Player::setStateMovement(std::unique_ptr<StatePlayerMovement> state)
{
	m_movement_state = std::move(state);
}

void Player::checkCam()	//called on every frame //Makes the game look smoother like the OG game
{
	if ((m_pos_Y < curLayer.getViewCenter() - const_cam_catchup_top_bound))	//first and topmost section of the camera, used for fast catching up to speeding player
	{
		if (Camera::getCamSpeed() < const_cam_catchup_top_max_speed)
		{
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_top_delta_speed * m_speedY * -1);
		}
		else
		{
			Camera::setCamSpeed(const_cam_catchup_top_max_speed);
		}
	}
	else if (m_pos_Y < curLayer.getViewCenter() - const_cam_catchup_bottom_bound && m_speedY < 0) //second, middle section of the camera, used for fine tuning
	{
		if (Camera::getCamSpeed() < const_cam_catchup_bottom_max_speed)
		{
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_bottom_delta_speed * m_speedY * -1);
		}
		else
		{
			Camera::setCamSpeed(const_cam_catchup_bottom_max_speed);
		}
	}
	else if (Camera::getCamSpeed() > Camera::getCamLevel()) //ensures smooth slowdown of camera after it's done relating to player
	{
		Camera::setCamSpeed(Camera::getCamSpeed() - Camera::getCamSpeed() * const_cam_catchup_slowdown_delta_speed);
	}
	else
	{
		Camera::setCamSpeed(Camera::getCamLevel());
	}
}

void Player::checkGameOver()
{
	
	if (m_pos_Y > curLayer.getViewCenter() + 240 && !Game::is_game_over)
	{
		is_on_ground = false;
		playSound(Menu::player_data.sound_jump_falling);
		Game::is_game_over = true;
	}
}

void Player::initializePosition()
{
	m_pos_X = const_player_start_pos_x;
	m_pos_Y = const_player_start_pos_y;
	m_player_sprite.setPosition(m_pos_X, m_pos_Y);
}

void Player::playSound(const sf::SoundBuffer& sound)
{
	if (Menu::bool_sound)
	{
		m_player_sound.setBuffer(sound);
		m_player_sound.playPitched();
	}
}

void Player::stopBGM()
{
	Menu::player_data.player_bgm.stop();
}

void Player::checkCandy()
{
	if (m_jump_strength == 3 && Score::combo_mode)
	{
		m_ec_combo.addCandy(m_pos_X, m_pos_Y, 1);
	}
	m_ec_combo.logic();
}

void Player::checkTimer()	//checks if the bound to start the timer is broken by the player
{
		if (!Timer::started && m_pos_Y < const_timer_start_bound && !Game::is_game_over)
		{
			Timer::started = true;
		}
}

void Player::render(sf::RenderWindow& window)
{
	curLayer.cam_posY = m_curr_platform->get()->m_layer.cam_posY;
	curLayer.speed_delta = m_curr_platform->get()->m_layer.speed_delta;
	curLayer.step = m_curr_platform->get()->m_layer.step;

	curLayer.view.reset(sf::FloatRect(0, m_curr_platform->get()->m_layer.cam_posY, 640, 480));

	m_player_sprite.setPosition((int)m_pos_X, (int)m_pos_Y);

	curLayer.render(window, m_player_sprite);
	m_ec_combo.render(window, false);
	if (milestone_mode)
	{
		ece_milestone.render(window, false);
		if (ece_milestone.getCount() == 0)
		{
			milestone_mode = false;
		}
	}
}

sf::Drawable& Player::getDrawable()
{
	return m_player_sprite;
}