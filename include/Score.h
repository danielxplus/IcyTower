#pragma once
#include <string.h>
#include <iostream>
#include <fstream>

#include "EyeCandyEngine.h"
#include "Object.h"
#include "Game.h"

class Score : public Object
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
	virtual void gameOverLogic() override;

	bool isComboMode();
	void changeScore(int i);

	int top_score_arr[3];
	static bool combo_mode;
	static int globalScore;
	static int globalTimesJumped;
	static int score; // total score

	// for combos:
	static int times_jumped;
	static int combo_score;
	static int combo_bar_height;
	static int 	m_floor_num;
private:

	bool first_iteration = true;

	void configureTextProperties();
	void setTextProperties(sf::Text& text, sf::String str, int size, sf::Vector2f scale, int outline_thickness, sf::Color outline_color, sf::Vector2f pos);

	void updatePositions();

	void changeColor();
	sf::Vector2i stop();

	void saveScore();
	void newHighScore();

	void rewardLogic();
	void handleRewards();

	void updateComboScore(int score);
	void startCombo();
	void endCombo();
	void comboLogic();

	void resetGameState();
	void configureStars();

	float reward_size;

	bool reward_mode,
		stop_mode,
		reward_animation_reset;

	int reward_index,
		temp_score,
		combo_score_total,
		best_combo,
		player_pos;

	sf::Text m_text_score;
	sf::Text m_text_floor_num;

	sf::Sprite combo_meter_sprite;
	sf::Sprite combo_meter_sprite_bar;

	sf::ConvexShape star;

	sf::Color m_color;

	sf::Music new_high_score,
		music_buffer;

	EyeCandyEngine eyecandyengine;

	Assets m_assets = m_assets.getInstance();

	enum Reward
	{
		Good, Sweet, Great, Super, Wow, Amazing, Extreme, Fantastic, Splendid, NoWay, RewardCount
	};

	void setRTProperties(sf::String file_name, Reward reward_string, float size);

	std::string reward_string[Reward::RewardCount];
};

void updateGlobalScore(int platform);