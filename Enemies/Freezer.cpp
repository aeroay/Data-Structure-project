#include "Freezer.h"

Freezer::Freezer(int id, int arrTime, int rld, int hlth, int pow, int spd) :Enemy(id, arrTime)
{
	this->Health = hlth;
	this->rldPeriod = rld;
	this->power = pow;
	this->speed = spd;
}

Freezer::~Freezer()
{
}

void Freezer::Freeze()
{
}


void Freezer::March()
{
	if (ACTV)
	{
		marchTowardCastle();
	}
}

bool Freezer::IsFrozen()
{
	if (status == FRST)
		return true;
}

void Freezer::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Freezer::GetHealth() const
{
	return Health;
}
