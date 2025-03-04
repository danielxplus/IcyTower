#pragma once

class Player; // Forward declaration

class StatePlayerMovement
{
public:
    virtual ~StatePlayerMovement() = default;
    virtual void handle(Player& player) = 0; // Pure virtual function for handling the state
};