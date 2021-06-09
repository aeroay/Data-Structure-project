#pragma once
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"
#include "../Enemies/Fighter.h"
#include "../Enemies/Freezer.h"
#include "../Enemies/Healer.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\Stack.h"
#include "..\Generic_DS\PQueue.h"

class Castle
{
	double			Health,			 //the current health in hte battle
					intialHealth;    //the satrting health i.e. before battle
	CASTLE_STATUS	status;
	double			power; // Power of each castle.
	//
	// TODO: Add More Data Members As Needed
	//
	int maxShoot;     // max #enemy the catle can shoot at every time step

public:

	void SetAllHealth(double h);
	double GetAllHealth() const;

	void SetHealth(double h);
	double GetHealth() const;
	CASTLE_STATUS GetStatus() const;
	void SetStatus(CASTLE_STATUS);
	//
	// TODO: Add More Member Functions As Needed
	//
	void SetPower(double p);
	double GetPower() const;
	void setMaxShoot(int max);
	void attackEnemies(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, int currTimeStep);
	void shootBullets(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers, int currTimeStep);
	void shootIce(PQueue<Fighter*>& fighters, Queue<Freezer*>& freezers, Stack<Healer*>& healers,  int currTimeStep);

};

