#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	int	ID;					//Each enemy has a unique ID (sequence number)
	int	ArrvTime;			//arrival time (time it starts to join battle)
	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	int			Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)

	// ==============================
	//		newly implemented
	// ===============================

	double		Health;		//Enemy health
	double		orgHealth;
	double		power;		 // Power of each enemy.
	int			rldPeriod;   //reload period
	int			speed;		 //enemy speed
	//int FirstShotDelay;					// first shot delay = T first shot - T arrival 
	//int KillDelay;					// kill delay = T KTS - T FD
	//int LifeTime;					// total enemy life time = FD + KD 
	int KillTimeStep;				// killing time step
	int firstShot;



public:
	Enemy(int id, int arrTime);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS s);
	
	void DecrementDist();                       // used only in demo
	void SetDistance(int );
	void marchTowardCastle();
	int GetDistance() const;
	int GetArrvTime() const;
	void setPower(int x);
	void setHealth(int x);
	double getHealth()const;
	void decreaseHealth(int x);
	void setRldPeriod(int x);
	void setSpeed(int x);
	// newly implemented members
	void setFirstShot(int t);
	int getFirstShot()const;
	void setKillTime(int t);
	int getKillTime()const;
	int getLifeTime()const;
	int getKillDelay()const;
	int getFirstShotDelay()const;
	int getFreezingPriorty()const;

	void check(Enemy*, int);

};

