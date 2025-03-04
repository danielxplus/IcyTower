#pragma once

class Player; // Forward declaration

class StatePlayerAnimation
{
public:
    virtual ~StatePlayerAnimation() = default;
    virtual void handle(Player& player) = 0; // Pure virtual function for handling the state
};