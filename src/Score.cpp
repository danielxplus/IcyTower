#include "Score.h"

bool registerScore = Factory::registerit("Score", []() -> std::unique_ptr<Object> { return std::make_unique<Score>(); });

bool Score::combo_mode;

int Score::globalScore;
int Score::times_jumped;
int Score::combo_score;
int Score::score;
int Score::combo_bar_height;
int Score::m_floor_num;

RainbowText m_rt_floors;
RainbowText m_rt_reward;

// =================================================================
void Score::setBasic(float& x, float& y, Layer& layer)
{
	this->m_layer = layer;
}

// =================================================================
void Score::init()
{
	m_color = sf::Color::Color(255, 0, 0, 255);
	reward_animation_reset = true;

	std::ifstream infile;
	infile.open("topscores.txt");

	for (int i = 0; i < 3; ++i)
	{
		infile >> top_score_arr[i];

	}

	infile.close();

	player_pos = 0;

	resetGameState();

	configureStars();

	configureTextProperties();

	combo_meter_sprite_bar.setTexture(m_assets.getTexture("combo_meter"));
	combo_meter_sprite.setTexture(m_assets.getTexture("combo_bar"));
	combo_meter_sprite.setPosition(20, 100);

	eyecandyengine.setLayer(m_layer);
	m_rt_floors.setLayer(m_layer);
	m_rt_reward.setLayer(m_layer);
}

// =================================================================
void Score::setTextProperties(sf::Text& text, sf::String str, int size, sf::Vector2f scale, int outline_thickness, sf::Color outline_color, sf::Vector2f pos)
{
	text.setString(str);
	text.setCharacterSize(size);
	text.setFont(DefaultFont::getFont());
	text.setCharacterSize(size);
	text.setScale(scale);
	text.setOutlineThickness(outline_thickness);
	text.setOutlineColor(outline_color);
	text.setPosition(pos);
}

// =================================================================
void Score::configureTextProperties()
{
	setTextProperties(m_rt_floors, "FLOORS", const_text_size_small, { 1,1 }, const_text_outline_small, const_color_outline, { 6, 245 });
	setTextProperties(m_rt_reward, "", const_text_size_large, { 1,1 }, const_text_outline_large, const_color_outline, { 320, 290 });

	setTextProperties(m_text_score, "SCORE: 0", 40, { 0.75,0.75 }, const_text_outline_medium, const_color_outline, { 10, 440 });
	setTextProperties(m_text_floor_num, "", const_text_size_medium, { 1,1 }, const_text_outline_medium, const_color_outline, { 40, 227 });

	m_text_floor_num.setPosition(40, 227);

	m_rt_floors.setPosition(6, 245);

	m_rt_reward.setPosition(320, 290);


	m_rt_floors.init();
	m_rt_reward.init();

	reward_string[Reward::Good] = "GOOD!";
	reward_string[Reward::Sweet] = "SWEET!";
	reward_string[Reward::Great] = "GREAT!";
	reward_string[Reward::Super] = "SUPER!";
	reward_string[Reward::Wow] = "WOW!";
	reward_string[Reward::Amazing] = "AMAZING!";
	reward_string[Reward::Extreme] = "EXTREME!";
	reward_string[Reward::Fantastic] = "FANTASTIC!";
	reward_string[Reward::Splendid] = "SPLENDID!";
	reward_string[Reward::NoWay] = "NO WAY!";

	for (std::string s : reward_string)
	{
		m_rt_reward.setString(s);
		m_rt_reward.getLocalBounds();
	}
	m_rt_floors.getLocalBounds();
}

// =================================================================
void Score::changeColor()
{
	m_text_score.setFillColor(m_color);

	if (combo_mode || reward_mode)
	{
		star.setFillColor(sf::Color(m_color.g, m_color.r, m_color.b, 255));
		m_text_floor_num.setFillColor(sf::Color(m_color.b, m_color.g, m_color.r, 255));
		m_color = RainbowText::changeColor(m_color, 51);
	}
	else
	{
		m_color = RainbowText::changeColor(m_color, 5);
	}
}

// =================================================================
void Score::rewardLogic()
{
	static int phase = 0;
	static int step = 0;

	if (reward_animation_reset)
	{
		phase = 0;
		reward_animation_reset = false;
	}

	if (phase == 0)	//init
	{
		m_rt_reward.setScale(0.05f, 0.05f);
		m_rt_reward.setRotation(0);
		step = 0;
		m_rt_reward.setString(reward_string[reward_index]);
		if (Menu::bool_sound)
		{
			music_buffer.setVolume(800);
			music_buffer.play();
		}

		phase++;
	}

	else if (phase == 1) // 1st sequence
	{
		if (step < 75)
		{
			m_rt_reward.scale({ reward_size ,reward_size });
			m_rt_reward.rotate(4.8);
			m_rt_reward.setOrigin(m_rt_reward.getLocalBounds().width / 2, m_rt_reward.getLocalBounds().height / 2);

			step++;
		}
		else phase++;
	}
	else if (phase == 2)
	{
		if (step < 150)
		{
			step++;
		}
		else phase++;
	}
	else if (phase == 3) // last sequence
	{
		if (m_rt_reward.getScale().x > 0.05f)
		{
			m_rt_reward.scale({ 0.85f ,0.85f });
			m_rt_reward.rotate(-18);
			m_rt_reward.setOrigin(m_rt_reward.getLocalBounds().width / 2, m_rt_reward.getLocalBounds().height / 2);
		}
		phase++;
	}
	else if (phase == 4)
	{
		phase = 0;
		reward_mode = false;
	}
	m_rt_floors.logic();
	m_rt_reward.logic();

}

// =================================================================
void Score::handleRewards()
{
	// lambda to map combo scores to rewards
	auto getReward = [](int combo_score) -> std::tuple<const char*, Reward, float> {
		if (combo_score < 10) return { "Good.mp3", Reward::Good, 1.028f };
		if (combo_score < 17) return { "Sweet.mp3", Reward::Sweet, 1.03f };
		if (combo_score < 25) return { "Great.mp3", Reward::Great, 1.032f };
		if (combo_score < 35) return { "Super.mp3", Reward::Super, 1.034f };
		if (combo_score < 50) return { "Wow.mp3", Reward::Wow, 1.04f };
		if (combo_score < 70) return { "Amazing.mp3", Reward::Amazing, 1.0375f };
		if (combo_score < 100) return { "Extreme.mp3", Reward::Extreme, 1.0375f };
		if (combo_score < 140) return { "Fantastic.mp3", Reward::Fantastic, 1.0375f };
		if (combo_score < 200) return { "Splendid.mp3", Reward::Splendid, 1.038f };
		return { "NoWay.mp3", Reward::NoWay, 1.0425f };
		};

	// Get the reward properties based on the combo score
	auto [sound_file, reward_string, size] = getReward(combo_score);

	setRTProperties(sound_file, reward_string, size);
}

// =================================================================
void Score::setRTProperties(sf::String file_name, Reward reward_string, float size)
{
	music_buffer.openFromFile(file_name);
	reward_index = reward_string;
	reward_size = size;

}

// =================================================================
void Score::startCombo()
{
	combo_mode = true;
	combo_meter_sprite_bar.setPosition(31, this->m_layer.cam_posY + 119);
	combo_bar_height = 100;
}

// =================================================================
void Score::updateComboScore(int score)
{
	times_jumped++;
	combo_score += score / 10;
	m_text_floor_num.setString(std::to_string(combo_score));
	m_text_floor_num.setOrigin(m_text_floor_num.getLocalBounds().width / 2, m_text_floor_num.getLocalBounds().height / 2);
}

// =================================================================
void Score::endCombo()
{
	combo_bar_height = 0;
	combo_meter_sprite_bar.setTextureRect(sf::IntRect(11, 19, 16, combo_bar_height));
	if (times_jumped >= 2) // times_jumped
	{
		combo_score_total += combo_score * combo_score;
		if (reward_mode)
		{
			reward_animation_reset = true;
		}
		else
		{
			reward_mode = true;
		}

		handleRewards();
		if (combo_score > best_combo)
		{
			best_combo = combo_score;
		}
		eyecandyengine.addCandy(320, 290, combo_score, 2, combo_score / 2);
	}
	combo_score = 0;
	times_jumped = 0;
	combo_mode = false;
}

// =================================================================
void Score::comboLogic()
{
	if (combo_bar_height > 0)
	{
		static bool skipper = 0;	//to prevent the bar from draining too quickly, drain it 1 px every 2 frames
		if (!skipper)
		{
			combo_bar_height--;
			combo_meter_sprite_bar.setTextureRect(sf::IntRect(11, 19, 16, combo_bar_height));
			combo_meter_sprite_bar.move(0, 1);
			skipper = 1;
		}
		else
		{
			skipper = 0;
		}
		m_rt_floors.logic();
	}
	else
	{
		endCombo();
	}
}

// =================================================================
void Score::configureStars()
{
	star.setPointCount(16);
	star.setPoint(0, sf::Vector2f(41, 18));
	star.setPoint(1, sf::Vector2f(59, 4));
	star.setPoint(2, sf::Vector2f(51, 26));
	star.setPoint(3, sf::Vector2f(74, 32));
	star.setPoint(4, sf::Vector2f(57, 39));
	star.setPoint(5, sf::Vector2f(62, 55));
	star.setPoint(6, sf::Vector2f(45, 44));
	star.setPoint(7, sf::Vector2f(34, 63));
	star.setPoint(8, sf::Vector2f(30, 45));
	star.setPoint(9, sf::Vector2f(7, 53));
	star.setPoint(10, sf::Vector2f(22, 39));
	star.setPoint(11, sf::Vector2f(1, 32));
	star.setPoint(12, sf::Vector2f(18, 27));
	star.setPoint(13, sf::Vector2f(5, 12));
	star.setPoint(14, sf::Vector2f(23, 17));
	star.setPoint(15, sf::Vector2f(28, 1));

	star.setOutlineThickness(4);
	star.setOutlineColor(const_color_outline);

	star.setPosition(0, 215);
}

// =================================================================
void Score::changeScore(int platform)
{
	m_floor_num = platform;
	int temp_plat = (platform - 1) * 10;

	if (player_pos + 20 <= temp_plat)	//jumped two or more floors - start combo
	{
		startCombo();
	}

	if (combo_mode)
	{
		if (player_pos + 20 <= temp_plat)
		{
			updateComboScore(temp_plat - player_pos);
		}
		else if (player_pos != temp_plat) //if on the same floor he was already on - do nothing
		{
			endCombo();
		}
	}

	score = temp_plat + combo_score_total;
	m_text_score.setString("SCORE: " + std::to_string(score));
	player_pos = temp_plat;
}

// =================================================================
void Score::saveScore()
{
	std::ifstream infile;
	infile.open("topscores.txt");

	for (int i = 0; i < 3; ++i)
	{
		infile >> top_score_arr[i];
	}

	if (score > top_score_arr[2])
	{
		top_score_arr[2] = score;
		for (int i = 0; i < 3 - 1; i++)
		{
			for (int j = 0; j < 3 - i - 1; j++)
			{
				if (top_score_arr[j] < top_score_arr[j + 1])
				{
					int temp = top_score_arr[j];
					top_score_arr[j] = top_score_arr[j + 1];
					top_score_arr[j + 1] = temp;
				}
			}
		}
	}

	std::ofstream outfile("topscores.txt"); // Output file stream object // debug
	if (!outfile)
	{
		std::cerr << "Failed to open the file for writing!" << std::endl;
		return;
	}

	for (int i = 0; i < 3; ++i)
	{
		outfile << top_score_arr[i] << std::endl;
	}
	outfile.close(); // Close the file
}

// =================================================================
void Score::newHighScore()
{
	if ((top_score_arr[0] < score) && (Menu::bool_sound))
	{
		new_high_score.openFromFile("Sounds\\NewHighScore.mp3"); // debug
		new_high_score.play();
	}
}

// =================================================================
sf::Vector2i Score::stop()
{
	stop_mode = true;
	sf::Vector2i values;
	values.x = player_pos / 10;
	values.y = best_combo;
	newHighScore();
	saveScore();
	return values;
}

// =================================================================
void Score::logic()
{
	if (combo_mode)
	{
		comboLogic();
	}
	if (reward_mode)
	{
		rewardLogic();
	}

	changeColor();
}

// =================================================================
void Score::render(sf::RenderWindow& window)
{
	updatePositions();

	m_layer.render(window, m_text_score);
	m_layer.render(window, combo_meter_sprite);

	if (combo_mode || reward_mode)
	{
		if (!Game::is_game_over)
		{
			m_layer.render(window, combo_meter_sprite_bar);
			m_layer.render(window, star);
		}
		m_layer.render(window, m_text_floor_num);
		m_rt_floors.render(window);
	}

	if (reward_mode || Game::is_game_over)
	{
		m_rt_reward.render(window);
	}
}

void Score::updatePositions()
{
	// Update positions of text, star, and sprites based on camera position
	star.setPosition(0, m_layer.cam_posY + 215);

	if (!Game::is_game_over)
	{
		m_text_floor_num.setString(std::to_string(combo_score));
		m_text_floor_num.setPosition(27, m_layer.cam_posY + 215);
		m_rt_floors.setPosition(6, m_layer.cam_posY + 245);
		m_rt_reward.setPosition(320, m_layer.cam_posY + 300);
		m_text_score.setPosition(10, m_layer.cam_posY + 440);
	}

	m_text_score.setString("SCORE: " + std::to_string(score));

	combo_meter_sprite_bar.setPosition(31, m_layer.cam_posY + 119);
	combo_meter_sprite.setPosition(20, m_layer.cam_posY + 100);
}

// =================================================================
void Score::gameOverLogic()
{
	static sf::Vector2i floor_combo_value;
	if (first_iteration)
	{
		floor_combo_value = stop();
		first_iteration = false;
	}

	// GAME OVER
	setTextProperties(m_rt_reward, "GAME OVER!", const_text_size_large, { 0.5,0.5 },
		const_text_outline_large, const_color_outline, { game_over_pos_x + 10, m_layer.cam_posY + 150 });
	m_rt_reward.setRotation(0);

	m_text_score.setPosition(game_over_pos_x + 100, m_layer.cam_posY + 300);

	if (Menu::bool_sound)
	{
		music_buffer.openFromFile("GameOver.mp3");
		music_buffer.play();
	}

	// BEST COMBO
	m_rt_floors.setString("Best combo: " + std::to_string(best_combo));
	m_rt_floors.setPosition(game_over_pos_x + 90, m_layer.cam_posY + 400);

	// BEST FLOOR
	m_text_floor_num.setString("Best floor: " + std::to_string(m_floor_num));
	m_text_floor_num.setFillColor(m_color);
	m_text_floor_num.setPosition(game_over_pos_x + 70, m_layer.cam_posY + 350);

	m_rt_reward.logic();
	m_rt_floors.logic();

	combo_mode = false;
	combo_mode = reward_mode = true; // For rendering
}


// =================================================================
bool Score::isComboMode()
{
	return combo_mode;
}

// =================================================================
void Score::reset()
{
	resetGameState();
	first_iteration = true;
	player_pos = 0;

	m_text_score.setOrigin(0, 0);
	m_text_score.setPosition(10, 440);
	m_text_score.setScale(0.75, 0.75);
	m_text_score.setString("SCORE: 0");

	m_rt_reward.setPosition(320, 290);
	m_rt_reward.setScale(0.5, 0.5);
	m_rt_reward.setString("");

	m_rt_floors.setString("FLOORS");
	m_rt_floors.setPosition(6, 245);
}

// =================================================================
void Score::resetGameState()
{
	times_jumped = 0;
	combo_mode = false;
	reward_mode = false;
	score = combo_score = combo_score_total = best_combo = 0;
	combo_bar_height = 0;
}

// =================================================================
void updateGlobalScore(int platform)
{

	static Score scoreInstance;
	scoreInstance.changeScore(platform);
}
