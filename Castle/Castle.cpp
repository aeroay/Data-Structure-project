#include "Castle.h"
#include <cmath>

void Castle::SetAllHealth(double h)
{
	intialHealth = h;
	Health = h;
}

double Castle::GetAllHealth() const
{
	return intialHealth;
}

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
	// active = 0
	// forsted = 1
	// destroyed = 2
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

void Castle::attackEnemies(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers,  int currTimeStep)
{
	shootBullets(fighters, freezers, healers, currTimeStep);
	shootIce(fighters, freezers, healers, currTimeStep);

}

void Castle::shootBullets(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, int currTimeStep)
{
	Fighter* pFtr;
	Freezer* pFrz;
	Healer* pHlr;

	for (int i = 0; i < maxShoot; i++)
	{
		if (!fighters.isEmpty())
		{
			fighters.dePQueue(pFtr);
			// decreasehealth according to castle shoot
			pFtr->decreaseHealth(power / pFtr->GetDistance());
			// set first shoot time step
			if (pFtr->getFirstShot()!= -1)
			pFtr->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
			if (pFtr->GetHealth() <= 0)
			{
				pFtr->setKillTime(currTimeStep);
				pFtr->SetStatus(KILD);
			}

		}

		else if (!healers.isEmpty())
		{
			healers.pop(pHlr);
			// decreasehealth according to castle shoot
			pHlr->decreaseHealth(power / pHlr->GetDistance());
			// set first shoot time step
			if (pHlr->getFirstShot() != -1)
				pHlr->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
			if (pHlr->GetHealth() <= 0)
			{
				pHlr->setKillTime(currTimeStep);
				pHlr->SetStatus(KILD);
				// if healer distance less than 5, castle exploit its ability to increase its health
				if (pHlr->GetDistance())
					Health *= 1.03;
			}

		}

		else if (!freezers.isEmpty())
		{
			freezers.dequeue(pFrz);
			// decreasehealth according to castle shoot
			pFrz->decreaseHealth(power / pFrz->GetDistance());
			// set first shoot time step
			if (pFrz->getFirstShot() != -1)
				pFrz->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
			if (pFrz->GetHealth() <= 0)
			{
				pFrz->setKillTime(currTimeStep);
				pFrz->SetStatus(KILD);
			}

		}
	}





}

void Castle::shootIce(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, int currTimeStep)
{

}

