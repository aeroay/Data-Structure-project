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
    void Fight();               //(Castle* pCas, int currTimeStep);
    void March();
    bool IsFrozen();
    void SetHealth(double h);
    double GetHealth() const;
    int getPriorty()const;

};

