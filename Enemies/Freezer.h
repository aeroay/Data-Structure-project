#pragma once
#include "Enemy.h"
//#include "../Castle/Castle.h"

class Freezer :
    public Enemy
{

public:
    Freezer(int id, int arrTime, int rld, int hlth, int pow, int spd);
    ~Freezer();
    void Freeze();    //(Castle* pCas, int currTimeStep);
    void March();
    bool IsFrozen();
    void SetHealth(double h);
    double GetHealth() const;
};

