#include "StateAnimations//StateOnEdge.h"
#include "Player.h"

void StateOnEdge::handle(Player& player)
{
    static int sound_counter = 0;

    if (player.m_player_sound.getStatus() != sf::Sound::Playing)
    {
        if (Menu::bool_sound)
        {
            player.m_player_sound.setBuffer(Menu::player_data.sound_edge);
        }

        if (sound_counter >= 45)
        {
            player.m_player_sound.playPitched();
            sound_counter = 0;
        }
    }

    sound_counter++;

    if (player.m_pos_X <= player.m_curr_platform->get()->getStartX() + 10)
    {
        player.m_player_sprite.setScale(-1, 1);
        player.m_player_sprite.setTextureRect(Animation::animation_edge1);
    }
    else
    {
        player.m_player_sprite.setScale(1, 1);
        player.m_player_sprite.setTextureRect(Animation::animation_edge2);
    }

}
