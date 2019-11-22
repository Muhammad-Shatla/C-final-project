#include "GUI.h"
#include "Player.h"
#include "Grid.h"
#include <iostream>

//This is a test code to test the Input and Output classes

int main()
{
	Grid *pGrid= new Grid;
	pGrid->RunApp();

	Player* p;

	cout << Cell::get_num_of_non_empty_cells();

	//cout << p->get_health() << p->get_lives() << p->get_score() << endl;

	delete pGrid;

	return 0;
}


