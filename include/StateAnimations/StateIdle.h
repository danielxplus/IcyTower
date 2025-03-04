#pragma once
#include "StatePlayerAnimation.h"
#include "Player.h"

class StateIdle : public StatePlayerAnimation
{
public:
    void handle(Player& player) override;
};