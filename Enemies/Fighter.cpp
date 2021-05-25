#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd) :Enemy(id, arrTime)
{
	this->Health = hlth;
	this-> rldPeriod = rld;
	this->power=pow;
	this->speed=spd;
}

Fighter::~Fighter()
{

}

void Fighter::Act()
{

}

void Fighter::Move()
{
	if (!IsFrozen())
	{
		DecrementDist();
	}
}

bool Fighter::IsFrozen()
{
	if (status == FRST)
		return true;
}

void Fighter::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Fighter::GetHealth() const
{
	return Health;
}
