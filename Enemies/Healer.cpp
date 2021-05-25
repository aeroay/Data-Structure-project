#include "Healer.h"

Healer::Healer(int id, int arrTime, int rld, int hlth, int pow, int spd) :Enemy(id, arrTime)
{
	this->Health = hlth;
	this->rldPeriod = rld;
	this->power = pow;
	this->speed = spd;
}

Healer::~Healer()
{
}

void Healer::Act()
{
}

void Healer::Move()
{
	if (!IsFrozen())
	{
		DecrementDist();
	}
}

bool Healer::IsFrozen()
{
	if (status == FRST)
		return true;
}

void Healer::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Healer::GetHealth() const
{
	return Health;
}
