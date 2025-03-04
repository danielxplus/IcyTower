#include "StateAnimations//StateJumping.h"

void StateJumping::handle(Player& player)
{
    if (player.m_jump_strength != 3)
    {
        if (player.m_pos_X < const_left_bound + 1 || player.m_pos_X > const_right_bound - 1 || player.m_speedX == 0)
        {
            player.m_player_sprite.setOrigin(14, 43);
            player.m_player_sprite.setTextureRect(Animation::animation_jump);
        }
        else
        {
            player.m_player_sprite.setScale(player.m_side, 1);
            if (player.m_speedY < -1)
            {
                player.m_player_sprite.setTextureRect(Animation::animation_jump1);
            }
            else if (player.m_speedY < 1)
            {
                player.m_player_sprite.setTextureRect(Animation::animation_jump2);
            }
            else
            {
                player.m_player_sprite.setTextureRect(Animation::animation_jump3);
            }
        }
    }
    else
    {
        player.m_player_sprite.setOrigin(21, 35);
        player.m_player_sprite.rotate(6);
        player.m_player_sprite.setTextureRect(Animation::animation_rotate);
    }
}
