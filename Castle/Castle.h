#pragma once
#include "..\Defs.h"
class Castle
{
	double			Health;
	CASTLE_STATUS	status;
	double			power; // Power of each castle.
	//
	// TODO: Add More Data Members As Needed
	//
	int maxShoot;     // max #enemy the catle ca shoot at every time step

public:

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
	
};

