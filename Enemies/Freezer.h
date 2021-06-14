#pragma once
#include "Enemy.h"


class Freezer :
    public Enemy
{

public:
    Freezer(int id, int arrTime, int rld, int hlth, int pow, int spd);
    ~Freezer();
    void Freeze();
    void March();
    bool IsFrozen();
    void SetHealth(double h);

};

