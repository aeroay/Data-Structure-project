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
	double		power;		 // Power of each enemy.
	int			rldPeriod;   //reload period
	int			speed;		 //enemy speed
	int FD;					// first shot delay 
	int KD;					// kill delay 
	int LT;					// total enemy life time
	int KTS;				// killing time step



public:
	Enemy(int id, int arrTime);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS s);
	
	void DecrementDist();
	void SetDistance(int );
	int GetDistance() const;
	int GetArrvTime() const;
	void setPower(int x);
	void setHealth(int x);
	void setRldPeriod(int x);
	void setSpeed(int x);
	// Virtual Functions: ----------------

	//virtual void Move() = 0;	//All enemies can move
	//virtual void Act() = 0;	//Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	//

};

