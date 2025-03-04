#pragma once
#include "StatePlayerAnimation.h"

class StateChock : public StatePlayerAnimation
{
public:
    void handle(Player& player) override
    {
        player.m_player_sprite.setTextureRect(Animation::animation_chock);
    }
};
