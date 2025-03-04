#pragma once
#include "StatePlayerAnimation.h"
#include "Player.h"

class StateJumping : public StatePlayerAnimation
{
public:
    void handle(Player& player) override;
};