#pragma once
#include "StatePlayerMovement.h"

class StateMovingRight : public StatePlayerMovement
{
public:
    void handle(Player& player) override 
    {
        if (player.m_speedX > 0 && player.m_side == -1) 
        {
            player.m_accelerating = false;
            player.delta_speed = const_player_slowdown_delta;
        }
        else 
        {
            player.m_side = 1;
            player.m_accelerating = true;
            player.delta_speed = 0.06f + player.m_speedX * 0.01f;
        }
        player.move();
    }
};
