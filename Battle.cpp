#include "Battle.h"
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &pCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:

		/*============================================*/
		/*The Simuation function will be written here*/
		/*===========================================*/
		// Jus_A_Demo() is currently commented

		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();
		break;
		

	}

	delete pGUI;
	
}

// ======================================

// Add the input function here to be used in RunSimulation() function.

// ======================================




//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{	
	
	pGUI->PrintMessage("Just a Demo. Enemies are read from a file");
	loadEnemy();

	pGUI->PrintMessage("Generating Enemies from the file ... CLICK to continue");
	pGUI->waitForClick();
	
	CurrentTimeStep = 0;
	
	
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	
	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		pGUI->waitForClick();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}		
}


//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	/*for(int i=0; i<DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);*/
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()	
{
	int InactiveCount = this->getMaxEnemy();
	Enemy* const *pE = Q_Inactive.toArray(InactiveCount);
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
	srand(time(0));
	for(int i=0; i< InactiveCount; i++)
	{
			switch(pE[i]->GetStatus())
		{
		case ACTV:
			pE[i]->DecrementDist();	//move the enemy towards the castle
			Prop = rand()%100;
			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE[i]->SetStatus(FRST); 
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
					{
						pE[i]->SetStatus(KILD);	
						ActiveCount--;
						KilledCount++;
					}
			
			break;
		case FRST:
			Prop = rand()%100;
			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE[i]->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
					{
						pE[i]->SetStatus(KILD);	
						FrostedCount--;
						KilledCount++;
					}

			break;
		}
	}
}

void Battle::setMaxEnemy(int max)
{
	this->EnemyCount = max;
}

int Battle::getMaxEnemy() const
{
	return EnemyCount;
}

void Battle::PrintWarAftermath()
{
	Castle* pC = this->GetCastle();

	if (pC->GetStatus() == DSTRD)
	{
		// game is lost
	}
	else
	{
		// game is won
	}
}

void Battle::loadEnemy()
{
	ifstream file("input.txt");

	int CH; //Castle Health
	int CP; // Castle Power
	int N; // max Enemies
	int M; // total enimies

	int ID;
	int TYP; // type
	int AT; // arrival time 
	int H; //health
	int POW; //power
	int RLD; // reload period 
	int SPD; // speed

	
	Castle* c = this->GetCastle();


		file >> CH >> N >> CP >> M;
		c->SetHealth(CH);
		c->setMaxShoot(N); 
		c->SetPower(CP);		
		setMaxEnemy(M);

		for (int i = 0; i < M; i++)
		{
			file >> ID >> TYP >> AT >> H >> POW >> RLD >> SPD;
			Enemy* e;

			if (TYP == 0)
				e = new Fighter(ID, AT, RLD, H, POW, SPD);
			else if (TYP == 2)
				e = new Freezer(ID, AT, RLD, H, POW, SPD);
			else
				e = new Healer(ID, AT, RLD, H, POW, SPD);

			Q_Inactive.enqueue(e);
		}
}
