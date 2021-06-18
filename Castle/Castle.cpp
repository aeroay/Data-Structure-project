#include "Castle.h"
#include <cmath>


Castle::Castle()
{
	status = ACTIVE;
}

void Castle::SetAllHealth(double h)
{
	intialHealth = h;
	Health = h;
}

double Castle::GetAllHealth() const
{
	return intialHealth;
}

void Castle::decreaseHealth(double h)
{
	Health -= h;
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

void Castle::attackEnemies(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, PQueue<Enemy*>& frosted,  int currTimeStep)
{

	if (status == ACTIVE)
	{
		
		int rnd = rand()%100 +1;
		double prob = rnd / 100.0;

		if (100*prob> 20)
		shootBullets(fighters, freezers, healers, frosted, currTimeStep);
		 else
		shootIce(fighters, freezers, healers, frosted, currTimeStep);
	}
}

void Castle::shootBullets(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, PQueue<Enemy*>& frosted, int currTimeStep)
{
	Fighter* pFtr;
	Freezer* pFrz;
	Healer* pHlr;
	Enemy* pE;
	// temporary DS as a repositery to help fill the original DS again
	PQueue<Fighter*> ftrs;
	Queue<Freezer*> frzs;
	Stack<Healer*> hlrs;
	PQueue<Enemy*> frstd;

	// dequeu or pop, then decrease health ...., push in a temporary DS
	for (int i = 0; i < maxShoot; i++)
	{
		
		if (!fighters.isEmpty())
		{
			fighters.dePQueue(pFtr);
			// decrease health according to castle shoot power
			pFtr->decreaseHealth(power / pFtr->GetDistance());
			// set first shoot time step
				pFtr->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
				pFtr->check(pFtr, currTimeStep);
			

			ftrs.enPQueue(pFtr, pFtr->getPriorty());
			
		}

		else if (!healers.isEmpty())
		{
			healers.pop(pHlr);
			// decreasehealth according to castle shoot
			pHlr->decreaseHealth(power / pHlr->GetDistance());
			// set first shoot time step
				pHlr->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
				pHlr->check(pHlr, currTimeStep);
				// if healer distance less than 5, castle exploit its ability to increase its health
				if (pHlr->GetDistance()&& pHlr->GetStatus()== KILD)
					Health *= 1.03;
			

			hlrs.push(pHlr);
			
		}

		else if (!freezers.isEmpty())
		{
			freezers.dequeue(pFrz);
			// decreasehealth according to castle shoot
			pFrz->decreaseHealth(power / pFrz->GetDistance());
			// set first shoot time step
				pFrz->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
				pFrz->check(pFrz, currTimeStep);

			frzs.enqueue(pFrz);
			
		}

		else if (!frosted.isEmpty())
		{
			frosted.dePQueue(pE);
			// decrease health according to castle shoot power
			pE->decreaseHealth(2*power / pE->GetDistance());
			// set first shoot time step
			pE->setFirstShot(currTimeStep);
			// check if killed and set the needed actions
			pE->check(pE, currTimeStep);


			frstd.enPQueue(pE, pE->getFreezingPriorty());
		}
	}
	
	PlaySound("shot.wav", NULL, SND_ASYNC);
	
	for (int i = 0; i < maxShoot; i++)
	{
		if (!ftrs.isEmpty())
		{
			ftrs.dePQueue(pFtr);
			fighters.enPQueue(pFtr, pFtr->getPriorty());
		}

		else if (!hlrs.isEmpty())
		{
			hlrs.pop(pHlr);
			healers.push(pHlr);
		}

		else if (!frzs.isEmpty())
		{
			frzs.dequeue(pFrz);
			freezers.enqueue(pFrz);
		}

		if (!frstd.isEmpty())
		{
			frstd.dePQueue(pE);
			frosted.enPQueue(pE, pE->getFreezingPriorty());
		}
	}
}
void Castle::shootIce(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, PQueue<Enemy*>& frosted, int currTimeStep)
{
	Fighter* pFtr;
	Freezer* pFrz;
	Healer* pHlr;
	// temporary DS as a repositery to help fill the original DS again
	PQueue<Fighter*> ftrs;
	Queue<Freezer*> frzs;
	Stack<Healer*> hlrs;
	

	// dequeu or pop, then decrease health ...., push in a temporary DS
	for (int i = 0; i < maxShoot; i++)
	{

		if (!fighters.isEmpty())
		{
			fighters.dePQueue(pFtr);
			// chech if frosted apriori
			if (pFtr->GetStatus() != FRST) 
			{
				pFtr->SetStatus(FRST);
				pFtr->setFrostTimeStep(currTimeStep);
			}
			// set first shoot time step
			pFtr->setFirstShot(currTimeStep);


			ftrs.enPQueue(pFtr, pFtr->getPriorty());

		}

		else if (!healers.isEmpty())
		{
			healers.pop(pHlr);
			// chech if frosted apriori
			if (pHlr->GetStatus() != FRST)
			{
				pHlr->SetStatus(FRST);
				pHlr->setFrostTimeStep(currTimeStep);
			}
			// set first shoot time step
			pHlr->setFirstShot(currTimeStep);
			


			if (pHlr->GetDistance() && pHlr->GetStatus() == KILD)
				Health *= 1.03;


			hlrs.push(pHlr);

		}

		else if (!freezers.isEmpty())
		{
			freezers.dequeue(pFrz);
			// chech if frosted apriori
			if (pFrz->GetStatus() != FRST)
			{
				pFrz->SetStatus(FRST);
				pFrz->setFrostTimeStep(currTimeStep);
			}
			// set first shoot time step
			pFrz->setFirstShot(currTimeStep);

			frzs.enqueue(pFrz);

		}

	}

	PlaySound("frz.wav", NULL, SND_ASYNC);

	for (int i = 0; i < maxShoot; i++)
	{
		if (!ftrs.isEmpty())
		{
			ftrs.dePQueue(pFtr);
			fighters.enPQueue(pFtr, pFtr->getPriorty());
		}

		else if (!hlrs.isEmpty())
		{
			hlrs.pop(pHlr);
			healers.push(pHlr);
		}

		else if (!frzs.isEmpty())
		{
			frzs.dequeue(pFrz);
			freezers.enqueue(pFrz);
		}
	}
}

