#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Assets.h"
#include "Animation.h"

enum ENUM_DIFFICULTY { easy, normal, hard };
enum ENUM_PLAYER_PRESET { harold, dave, kirby };
enum ENUM_GAME_STATES { ReturnToMenu, InGame, GameOver, Resetting, Loading };

const int const_cam_start_step = 512;
const float const_cam_speed_delta = 0.125f;
const int const_cam_catchup_top_bound = 200;
const int const_cam_catchup_bottom_bound = 100;
const int const_cam_catchup_top_max_speed = 25;
const int const_cam_catchup_bottom_max_speed = 15;
const float const_cam_catchup_top_delta_speed = 0.066f;
const float const_cam_catchup_bottom_delta_speed = 0.1f;
const float const_cam_catchup_slowdown_delta_speed = 0.05f;

const float const_eyecandy_gravity = 0.075f;

const int const_dist_between_platforms = 80;

const float const_player_gravity = 0.175;
const float const_player_high_jump_gravity = -5;
const float const_player_start_pos_x = 180;
const float const_player_start_pos_y = 417;
const int const_left_bound = 87;
const int const_right_bound = 553;
const int const_chock_anim_trigger_bound = 140;
const float const_player_xspeed_max = 6;
const float const_player_yspeed_max = 6;
const float const_player_slowdown_delta = 0.6;
const float const_player_accelerate_delta = 0.085f;
const float const_player_friction_delta = 0.14f;

const sf::Color const_color_outline(1, 26, 51, 255);
const int const_text_menu_size = 75;
const int const_text_size_small = 20;
const int const_text_size_medium = 30;
const int const_text_size_large = 140;
const int const_text_outline_small = 1;
const int const_text_outline_medium = 2;
const int const_text_outline_large = 5;

const int const_timer_start_pos_x = 42;
const int const_timer_start_pos_y = 56;
const int const_timer_start_bound = 20;

const int const_enemy_start_pos_x = 50;
const int const_enemy_start_pos_y = 70;

const int game_over_pos_x = 130;

const sf::Vector2f const_menu_title_pos = { 50.0f, 50.0f };

const sf::Vector2f const_button_def_size = { 1.0f,1.0f};
const sf::Vector2f const_button_hover_size = { 1.1f,1.1f };

const sf::Vector2f const_button_play_pos = { 50.0f,220.0f };
const sf::Vector2f const_button_lead_pos = { 50.0f,310.0f };
const sf::Vector2f const_button_instruc_pos = { 50.0f,410.0f };
const sf::Vector2f const_button_settings_pos = { 50.0f,510.0f };
const sf::Vector2f const_button_exit_pos = { 50.0f,600.0f };
const sf::Vector2f const_button_logo_pos = { 650.0f,-120.0f };

const sf::Vector2f const_button_char_pos = { 50.0f,110.0f };
const sf::Vector2f const_button_sound_pos = { 50.0f,480.0f };
const sf::Vector2f const_button_return_pos = { 100.0f,600.0f };

const sf::Vector2f const_char_pos = { 900.0f,110.0f };