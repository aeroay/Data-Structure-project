#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd) :Enemy(id, arrTime)
{
	this->Health = hlth;
	this-> rldPeriod = rld;
	this->power=pow;
	this->speed=spd;

	priorty = sqrt(2) * pow * spd * hlth / rld;

}

Fighter::~Fighter()
{

}

void Fighter::Fight()
{
}


void Fighter::March()
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

int Fighter::getPriorty() const
{
	return priorty;
}
