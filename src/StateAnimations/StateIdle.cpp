#include "StateAnimations//StateIdle.h"

void StateIdle::handle(Player& player)
{
    static int animation_counter = 0;

    if (animation_counter < 25)
    {
        player.m_player_sprite.setTextureRect(Animation::animation_idle1);
    }
    else if (animation_counter < 50)
    {
        player.m_player_sprite.setTextureRect(Animation::animation_idle2);
    }
    else if (animation_counter < 75)
    {
        player.m_player_sprite.setTextureRect(Animation::animation_idle1);
    }
    else if (animation_counter < 100)
    {
        player.m_player_sprite.setTextureRect(Animation::animation_idle3);
    }
    else
    {
        animation_counter = 0;
    }
    animation_counter++;
}