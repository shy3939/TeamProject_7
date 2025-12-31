#pragma once

class Player;

class Field
{
public:
    virtual ~Field() = default;
    virtual void Enter(Player* player) = 0;
};