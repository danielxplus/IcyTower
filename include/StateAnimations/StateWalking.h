#pragma once
#include "StatePlayerAnimation.h"
#include "StateIdle.h"
#include "Player.h"

class StateWalking : public StatePlayerAnimation
{
public:
    void handle(Player& player) override;
};
