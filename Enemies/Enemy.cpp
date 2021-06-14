#include "Enemy.h"


Enemy::Enemy(int id, int arrTime):ID(id),ArrvTime(arrTime)
{
	SetDistance(MaxDistance);
	SetStatus(INAC);
	firstShot = -1;
	KillTimeStep = -1;

}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MinDistance;
}

void Enemy::marchTowardCastle()
{
	SetDistance(Distance - (Health < 0.5 * orgHealth ? (int)speed / 2 : speed));
}

int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy::setPower(int x)
{
	power = x;
}

void Enemy::setHealth(int x)
{
	// sets the value of the original ealth of the enemy
	orgHealth = x;
	Health = x;
}

double Enemy::getHealth() const
{
	return Health;
}

void Enemy::setRldPeriod(int x)
{
	rldPeriod = x;
}

void Enemy::setSpeed(int x)
{
	speed = x;
}

void Enemy::decreaseHealth(int x)
{
	Health -= x;
}

int Enemy::getFirstShotDelay() const
{
	return firstShot - ArrvTime;
}

int Enemy::getFreezingPriorty() const
{
	return 0;
}

void Enemy::check(Enemy* pE, int currTimeStep)
{
	if (pE->getHealth() <= 0)
	{
		pE->setKillTime(currTimeStep);
		pE->SetStatus(KILD);
	}


}



void Enemy::setFirstShot(int t)
{
	if (firstShot==-1)
	firstShot = t;

}

int Enemy::getFirstShot() const
{
	return firstShot;
}

void Enemy::setKillTime(int t)
{
	KillTimeStep = t;
}

int Enemy::getKillTime() const
{
	return KillTimeStep;
}

int Enemy::getLifeTime() const
{
	return KillTimeStep-ArrvTime;
}

int Enemy::getKillDelay() const
{
	return KillTimeStep-firstShot;
}


