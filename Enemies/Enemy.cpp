#include "Enemy.h"


Enemy::Enemy(int id, int arrTime):ID(id),ArrvTime(arrTime)
{
	SetDistance(MaxDistance);
	SetStatus(INAC);
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
		Distance = MaxDistance;
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
	Health = x;
}

void Enemy::setRldPeriod(int x)
{
	rldPeriod = x;
}

void Enemy::setSpeed(int x)
{
	speed = x;
}

