#include "StateAnimations//StateWalking.h"

void StateWalking::handle(Player& player)
{
    static int animation_counter = 0;

    // walking animation based on pos and speed

    if (player.m_pos_X < const_left_bound + 1) // going right
    {
        player.m_player_sprite.setScale(1, 1);
        player.m_player_sprite.setTextureRect(Animation::animation_walk1);
    }
    else if (player.m_pos_X > const_right_bound - 1) // going left
    {
        player.m_player_sprite.setScale(-1, 1);
        player.m_player_sprite.setTextureRect(Animation::animation_walk1);
    }
    else if (player.m_speedX > 0 && !player.checkBoundaries())
    {
        player.m_player_sprite.setScale(player.m_side, 1);
        if (animation_counter < 20)
        {
            player.m_player_sprite.setTextureRect(Animation::animation_walk1);
        }
        else if (animation_counter < 100)
        {
            player.m_player_sprite.setTextureRect(Animation::animation_walk2);
        }
        else if (animation_counter < 150)
        {
            player.m_player_sprite.setTextureRect(Animation::animation_walk3);
        }
        else if (animation_counter < 200)
        {
            player.m_player_sprite.setTextureRect(Animation::animation_walk4);
        }
        else
        {
            animation_counter = 0;
        }
        animation_counter += player.m_speedX;
    }
    else
    {
        // Transition to Idle state
        player.setStateAnimation(std::make_unique<StateIdle>());
    }
}
