#include "Battle.h"
#include "GUI\GUI.h"
#include <time.h>

int main()
{
	srand(time(0));
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	
	delete pGameBattle;
	
}
