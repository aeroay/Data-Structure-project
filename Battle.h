#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Freezer.h"
#include "Enemies\Healer.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS\Stack.h"
#include "Generic_DS\PQueue.h"
#include "GUI\GUI.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle pCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	PQueue<Fighter*> Q_Fighter;		//Queue of fighter 
	PQueue<Enemy*> Q_Frozen;		//Queue of frosted enemies 
	Stack<Healer*> S_Healer;
	Queue<Freezer*> Q_Freezer;

	

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>

	const int WindWidth = 1200, WindHeight = 650,		//Window width and height
		StatusBarHeight = 150,	//Status Bar Height
		MenuBarHeight = 0,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 80;	//Width of each item in menu bar menu

	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	GUI* getGUI();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived


	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	//
	// TODO: Add More Member Functions As Needed
	//

	void loadEnemy();
	void setMaxEnemy(int max);
	int getMaxEnemy()const;
	void PrintWarAftermath();
	void GUImode(PROG_MODE mode);
	void updateWarStatus();
};

