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

	Actv_Ftr=0, Actv_Hlr=0, Actv_Frz=0;

	Kld_Frz = 0;
	Kld_Ftr = 0;
	Kld_Hlr = 0;

	frosted_Frz = 0;
	frosted_Ftr = 0;
	frosted_Hlr = 0;

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

GUI* Battle::getGUI()
{
	return pGUI;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		GUImode(MODE_INTR);
		break;

	case MODE_STEP:
		GUImode(MODE_STEP);
		break;

	case MODE_SLNT:
		GUImode(MODE_SLNT);
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
		updateWarStatus(CurrentTimeStep);
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

	int ftrs;
	Fighter* const* FighterList = Q_Fighter.toArray(ftrs);
	for (int i = 0; i < ftrs; i++)
		pGUI->AddToDrawingList(FighterList[i]);

	int kld;
	Enemy* const* KilledList = Q_Killed.toArray(kld);
	for (int i = 0; i < kld; i++)
		pGUI->AddToDrawingList(KilledList[i]);

	int frz;
	Freezer* const* FreezerList = Q_Freezer.toArray(frz);
	for (int i = 0; i < frz; i++)
		pGUI->AddToDrawingList(FreezerList[i]);

	int hlr;
	Healer* const* HealerList = S_Healer.toArray(hlr);
	for (int i = 0; i < hlr; i++)
		pGUI->AddToDrawingList(HealerList[i]);






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
		//AddtoDemoList(pE);		//move it to demo list (for demo purposes)

		Fighter* pFtr = dynamic_cast<Fighter*>(pE);
		Healer* pHlr = dynamic_cast<Healer*>(pE);
		Freezer* pFrz = dynamic_cast<Freezer*>(pE);

		if (pFtr != NULL)
			Q_Fighter.enPQueue(pFtr, pFtr->getPriorty());
		
		if (pHlr != NULL)
			S_Healer.push(pHlr);

		if (pFrz != NULL)
			Q_Freezer.enqueue(pFrz);
	
		
	}
}


void Battle::RunMode(string mode_name, int flag)
{
	
	pGUI->PrintMessage("Welcome to "+ mode_name +" mode, click to continue");
	pGUI->waitForClick();

	loadEnemy();

	pGUI->PrintMessage("Generating Enemies from the file ... CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
	updateWarStatus(CurrentTimeStep);

	while (KilledCount < EnemyCount && this->GetCastle()->GetHealth()>0)	//as long as some enemies are alive (should be updated in next phases)
	{
	
		ActivateEnemies();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();	
		pGUI->UpdateInterface(CurrentTimeStep);
		updateWarStatus(CurrentTimeStep);
		letTheHungerGamesBegin();    // a function that makes the castle interact with enimes and vise versa
		CurrentTimeStep++;
		switch (flag)
		{
		case 0:
			pGUI->waitForClick();
			break;
		case 1:
			Sleep(1000);
			break;
		case 2:
			// silent mode
			break;
		} 

	}
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();

	pGUI->UpdateInterface(CurrentTimeStep);
	updateWarStatus(CurrentTimeStep);

	if (KilledCount >= EnemyCount)
		battleStatus = "WIN";
	else if (GetCastle()->GetHealth() <= 0)
		battleStatus = "LOSE";
	else
		battleStatus = "DRAWN";
	
	PrintWarAftermath();
	char c;
	//cin >> c;
}

void Battle::letTheHungerGamesBegin()
{
	// 0- extract enemies from DS to array drawing
	Fighter* pFtr;
	Freezer* pFrz;
	Healer* pHlr;
	Castle* pCas = GetCastle();

	updateNumbers();         //sets active/kiled/frosted enemies count
	// temporary DS as a repositery to help fill the original DS again
	PQueue<Fighter*> ftrs;
	Queue<Freezer*> frzs;
	Stack<Healer*> hlrs;
	
	// 1- castle shoot the enemy 
	pCas->attackEnemies(Q_Fighter,Q_Freezer,S_Healer,CurrentTimeStep);

	// 2- enemy shoot the castle 
	for (int i = 0; i < getActv_E(); i++)
	{
		if (!Q_Fighter.isEmpty())
		{
			Q_Fighter.dePQueue(pFtr);
			if (pFtr->GetStatus() == ACTV)
			{
				
				double shoot = pFtr->Fight();
				pCas->decreaseHealth(shoot);
				pFtr->March();
				ftrs.enPQueue(pFtr, pFtr->getPriorty());
			}
			
		else if (pFtr->GetStatus() == KILD)
			{
				Q_Killed.enqueue(pFtr);
				Kld_Ftr++;
				Actv_Ftr--;
			}
			else if (pFtr->GetStatus() == FRST)
			{
				Q_Frozen.enPQueue(pFtr, pFtr->getFreezingPriorty());
				frosted_Ftr++;
				Actv_Ftr--;
			}
		}
		if (!S_Healer.isEmpty())
		{
			S_Healer.pop(pHlr);
			if (pHlr->GetStatus() == ACTV)
			{
				//pHlr->Heal();
				pHlr->March();
				hlrs.push(pHlr);
			}
		else if (pHlr->GetStatus() == KILD)
			{
				Q_Killed.enqueue(pHlr);
				Kld_Hlr++;
				Actv_Hlr--;
			}
			else if (pHlr->GetStatus() == FRST)
			{
				Q_Frozen.enPQueue(pHlr, pHlr->getFreezingPriorty());
				frosted_Hlr++;
				Actv_Hlr--;
			}
			
			
		}
		if (!Q_Freezer.isEmpty())
		{
			Q_Freezer.dequeue(pFrz);

			if (pFrz->GetStatus() == ACTV)
			{

				pFrz->Freeze();
				pFrz->March();
				frzs.enqueue(pFrz);
			}
		else if (pFrz->GetStatus() == KILD)
			{
				Q_Killed.enqueue(pFrz);
				Actv_Frz--;
				Kld_Frz++;
				
			}
			else if (pFrz->GetStatus() == FRST)
			{
				Q_Frozen.enPQueue(pFrz, pFrz->getFreezingPriorty());
				Actv_Frz--;
				frosted_Frz++;
			}
		}
	}
	// return enemy to their orginal DS 
	for (int i = 0; i < getActv_E(); i++)
	{
		if (!ftrs.isEmpty())
		{
			ftrs.dePQueue(pFtr);
			Q_Fighter.enPQueue(pFtr, pFtr->getPriorty());
		}

		if (!hlrs.isEmpty())
		{
			hlrs.pop(pHlr);
			S_Healer.push(pHlr);
		}
		if (!frzs.isEmpty())
		{
			frzs.dequeue(pFrz);
			Q_Freezer.enqueue(pFrz);
		}
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
	Enemy* pE;

	ofstream out("BattleOutputFile.txt");


	out << "Game is " + battleStatus << endl;
	out << "KTS\tID\tFD\tKD\tLT" << endl;

	int enemy_id;
	int enemy_KDS;
	int enemy_FD;
	int enemy_KD;
	int enemy_LT;
	int total_FD = 0;
	int total_KD = 0;

	while (Q_Killed.dequeue(pE))
	{
		enemy_id = pE->GetID();
		enemy_KDS = pE->getKillTime();
		enemy_FD = pE->getFirstShotDelay();
		enemy_KD = pE->getKillDelay();
		enemy_LT = pE->getLifeTime();
		total_FD += enemy_FD;
		total_KD += enemy_KD;

		out << enemy_KDS << "\t" << enemy_id << "\t" << enemy_FD << "\t" << enemy_KD << "\t" << enemy_LT << endl;
	}

	double average_FD = (double)total_FD / EnemyCount;
	double average_KD = (double)total_KD / EnemyCount;

	if (battleStatus == "WIN")
	{
		out << "Total Enemies = " << EnemyCount << endl;
		out << "Castle total damage = " << pC->GetAllHealth() - pC->GetHealth() << endl;
	}
	else
	{
		out << "Killed Enemies = " << KilledCount << endl;
		out << "Alive Enemies = " << EnemyCount - KilledCount << endl;
	}

	out << "Average First-Shot Delay = " << average_FD << endl;
	out << "Average Kill Delay = " << average_KD << endl;

	out.close();

}

void Battle::GUImode(PROG_MODE mode)
{
	
	if (mode == MODE_INTR)
	{
		RunMode("Interactive", 0);
	}
	else if (mode == MODE_STEP)
	{
		RunMode("Step", 1);
	}
	else // silent mode
	{
		RunMode("Silent", 2);
	}
}

void Battle::updateWarStatus(int CurrentTimeStep)
{
	string ts = "Current time step is: ";
	string ch = "Castle health: ";
	string cs = "and its status: ";
	string actv = "Number of active: ";
	string frz = "Number of frozen: ";
	string kld = "Number of killed: ";

	Castle* c = this->GetCastle();
	GUI* gui = this->getGUI();
	gui->ClearStatusBar();

	
	string strTimestep = to_string(CurrentTimeStep);
	string c_health = to_string(c->GetHealth());
	string actv_E = to_string(getActv_E());
	string frz_E = to_string(getFrz_E());
	string kld_E = to_string(getKld_E());
	


	gui->DrawString(10, WindHeight - (int)(StatusBarHeight - 5), ts + strTimestep);
	gui->DrawString(10, WindHeight - (int)(StatusBarHeight - 30), ch+ c_health);
	gui->DrawString(10, WindHeight - (int)(StatusBarHeight - 55), actv+ actv_E);
	gui->DrawString(10, WindHeight - (int)(StatusBarHeight - 80), frz+ frz_E);
	gui->DrawString(10, WindHeight - (int)(StatusBarHeight - 105), kld+ kld_E);

}

int Battle::getActv_E() const
{
	  
	return ActiveCount;
}

void Battle::setActv_E()
{
	ActiveCount = Actv_Frz + Actv_Ftr + Actv_Hlr;
}

int Battle::getFrz_E() const
{
	return FrostedCount;
}

void Battle::setFrz_E()
{
	FrostedCount = frosted_Frz + frosted_Ftr + frosted_Hlr;
}

int Battle::getKld_E() const
{
	return KilledCount;
}

void Battle::setKld_E()
{
	KilledCount = Kld_Frz + Kld_Ftr + Kld_Hlr;
}

void Battle::updateNumbers()
{
	if (!Q_Fighter.isEmpty())
	Q_Fighter.toArray(Actv_Ftr);

	if (!S_Healer.isEmpty())
	S_Healer.toArray(Actv_Hlr);

	if (!Q_Freezer.isEmpty())
	Q_Freezer.toArray(Actv_Frz);

	setActv_E();
	setFrz_E();
	setKld_E();

}




void Battle::loadEnemy()
{
	pGUI->PrintMessage("Please enter the input file name, without .txt");
	string fileName = pGUI->GetString(); //file name to be input by the user
	ifstream file(fileName + ".txt");

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
		c->SetAllHealth(CH);   
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
