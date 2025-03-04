#pragma once
#include "StatePlayerMovement.h"

class StateNotMoving : public StatePlayerMovement
{
public:
    void handle(Player& player) override 
    {
        if (player.m_speedX > 0) 
        {
            player.m_accelerating = false;
            player.delta_speed = 0.04f + player.m_speedX * 0.01f;
            player.move();
        } else 
        {
            player.m_side = 0; // No movement
        }
    }
};
