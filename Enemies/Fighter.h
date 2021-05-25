#pragma once
#include "Enemy.h"


class Fighter :
    public Enemy
{
    double		priorty;
public:
    Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd);
    ~Fighter();
    void Act();
    void Move();
    bool IsFrozen();
    void SetHealth(double h);
    double GetHealth() const;

};

