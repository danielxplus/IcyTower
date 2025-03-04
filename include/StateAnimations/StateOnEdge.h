#pragma once
#include "StatePlayerAnimation.h"

class StateOnEdge : public StatePlayerAnimation
{
public:
    void handle(Player& player) override;
};