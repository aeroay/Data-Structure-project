#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int rld, int hlth, int pow, int spd) :Enemy(id, arrTime)
{
	this->Health = hlth;
	orgHealth = hlth;
	this-> rldPeriod = rld;
	this->power=pow;
	this->speed=spd;

	priorty = sqrt(2) * pow * spd * hlth / rld;

}

Fighter::~Fighter()
{

}

double Fighter::Fight()
{
	if (Health<0.5*orgHealth)
		return (0.5 / Distance * power);
	
	else
		return (1.0/(double)Distance * power);
}


void Fighter::March()
{
	if (ACTV)
	{
		marchTowardCastle();
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



int Fighter::getPriorty() const
{
	return priorty;
}
