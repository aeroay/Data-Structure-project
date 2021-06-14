#pragma once
#include "Enemy.h"
//#include "../Castle/Castle.h"


class Fighter :
    public Enemy
{
    int		priorty;
public:
    Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd);
    ~Fighter();
    double Fight();
    void March();
    bool IsFrozen();
    void SetHealth(double h);
    int getPriorty()const;

};

