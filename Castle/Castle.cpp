#include "Castle.h"

void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

CASTLE_STATUS Castle::GetStatus() const
{
	return status;
}

void Castle::SetStatus(CASTLE_STATUS s)
{
	status = s;
}

void Castle::SetPower(double p)
{
	this->power = p;
}

double Castle::GetPower() const
{
	return power;
}

void Castle::setMaxShoot(int max)
{
	this->maxShoot = max;
}
