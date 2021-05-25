#pragma once
#include "Enemy.h"


class Healer :
    public Enemy
{
    
    public:
        Healer(int id, int arrTime, int rld, int hlth, int pow, int spd);
        ~Healer();
        void Act();
        void Move();
        bool IsFrozen();
        void SetHealth(double h);
        double GetHealth() const;
};

