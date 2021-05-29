#pragma once
#include "Enemy.h"


class Fighter :
    public Enemy
{
    int		priorty;
public:
    Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd);
    ~Fighter();
    void Fight();
    void March();
    bool IsFrozen();
    void SetHealth(double h);
    double GetHealth() const;
    int getPriorty()const;

};

