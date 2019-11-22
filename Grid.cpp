#include "Grid.h"

#include "Player.h"
#include "EmptyCell.h"
#include "PlayerCell.h"
#include "EnemyCell.h"
#include "ObstacleCell.h"
#include "HeartCell.h"
#include "WingsCell.h"
#include "EggCell.h"
#include "ArmourCell.h"
#include "GoalCell.h"
#include "BombCell.h"
#include "FreezerCell.h"
#include <fstream>
#include "GUI.h"

#include<iostream>
using namespace std;



Grid::Grid() 
{
	// initializes all the GameObject pointer of the List to NULL
	for (int i = 0; i < NumRowCells; i++)
	{
		for (int j = 0; j < NumColumnCells; j++)		{
			
			GameCells[i][j] = new EmptyCell(i,j);	//start with all cells as empty cells
		}
	}
	pGUI = new GUI;
	DrawAllCells();
	
}



/////////////////////////////////////////////////////////////////////////////////////////////
// Moves the entered position in the passed direction if possible
// updates currentCell if move takes place
// Note: It returns bool indicating if a move occured or not
bool Grid::MoveIfPossible(Cell* pCurrentCell, ActionType dir) 
{
	
	//Calculate the row and col of the cell to move to
	//First initialize them as current row and col
	int playerOldRow = pCurrentCell->getRow();
	int playerOldCol = pCurrentCell->getCol();

	int TargetRow = playerOldRow;
	int TargetCol = playerOldCol ; 

	
	switch(dir)
	{
	case MOVE_UP:
		TargetRow--;
		break;
	case MOVE_DOWN:
		TargetRow++;
		break;
	case MOVE_LEFT:
		TargetCol--;
		break;
	case MOVE_RIGHT:
		TargetCol++;;
		break;
	}

	if( !IsValidCell(TargetRow, TargetCol))
		return false;

	//get the target cell
	Cell *pTargetCell = GameCells[TargetRow][TargetCol];

	if(!pTargetCell->ActOn(player))	//The target cell is an obstacle ==> no action should be taken
		return false;

	//The target cell is not an obstacle and has acted on the player
	//The player position should be updated to the target cell
	
	//Player should be moved to the target cell
	//1-delete the target cell and make it point to the PlayerCell
	setCell(TargetRow,TargetCol, pCurrentCell);

	//2- update player position
	pCurrentCell->SetRow(TargetRow);
	pCurrentCell->SetCol(TargetCol);

	//3- Convert the old player position to an Empty cell
	GameCells[playerOldRow][playerOldCol] = new EmptyCell(playerOldRow,playerOldCol);

	//4- Redraw both cells
	pGUI->DrawCell(GameCells[TargetRow][TargetCol]);
	pGUI->DrawCell(GameCells[playerOldRow][playerOldCol]);

	return true;
}

void Grid::DrawAllCells() const	
{
	// Draw Empty Grid
	pGUI->ClearGridArea();

	// Draw all the GameObject of the Grid
	for (int i = 0; i < NumRowCells; i++)
		for (int j = 0; j < NumColumnCells; j++)
			pGUI->DrawCell(GameCells[i][j]);
}

void Grid::setCell(int row, int col, Cell* pCell)  /*we use setCell by giving it ints for x and y so that it deletes */
{	
	if(GameCells[row][col])
		delete GameCells[row][col];	//if cell ptr is not null, delete it first
	
	GameCells[row][col] = pCell;

}


GUI * Grid::getGUI() const
{
	return pGUI;
}
///////////////////////////////////////////////////////////////////
//				Action-related functions
///////////////////////////////////////////////////////////////////

ActionType Grid::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pGUI->GetUserAction( ); 
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void Grid::ExecuteAction(ActionType ActType) 
{

	 

//H.... you need to declare the below variables outside the case otherwise they don't run if the case isn't met and you get an error.
//////////////////////////////// My Cell x and cell y variables used in the different cases///////////////////////////////////
	int Obstacle_Cell_x, Obstacle_Cell_y;
	int Empty_Cell_x, Empty_Cell_y;
	int Enemy_Cell_x, Enemy_Cell_y;
	int Heart_Cell_x, Heart_Cell_y;
	int Wings_Cell_x, Wings_Cell_y;
	int Egg_Cell_x, Egg_Cell_y;	
	int Armour_Cell_x, Armour_Cell_y;
	int Goal_Cell_x, Goal_Cell_y;
	int Bomb_Cell_x, Bomb_Cell_y;
	int Freezer_Cell_x, Freezer_Cell_y;
////////////////////////////////////////////////////////////////////////////

	// According to Action Type, create the corresponding action object	
	switch (ActType)
	{
	case LOAD:
		// Call Load function to load game from a file
		load();
		break;

	case SAVE:
		// Call Save function to Save current game to a file
		save_all();
		break;

	case START:	//start game 
		pGUI->setInterfaceMode(MODE_GAME);
		break;

	case PAUSE:	//pause game
		pGUI->setInterfaceMode(MODE_MENU);
		break;

/////////////////////////////////My added Cases/////////////////////////////////////////////////////////////////////////

	case ENEMY: 
		pGUI->PrintMessage("enemy clicked");  /* we use the print function to print messages in the status barthis one
											     was to identify that a cell was clicked and states the cell type*/
		int x, y;  
		pGUI->GetPointClicked(x,y);  /* the GetPointClicked function is accessed through the pGUI pointer that points to the GUI class
									 we declared and initialized the pGUI pointer it in the Grid.h file*/

		Enemy_Cell_x = x / 50;     /*we adjust the x and y coordinates by divinfing them by their width or height to get the cell or row number*/
		Enemy_Cell_y = (y / 50)-1; /* we deduct 1 from the Y coordinate i.e the row number to account for menu bar height */

		GridChecker(Enemy_Cell_x, Enemy_Cell_y);  /* a function we defined to check for the validity of the click, it should nither be on
									  on the player cell or the status or menu bar, if you missclick you will get an error message
									  asking you to click within the grid and will prompt you for another click* the fucntion is defined 
									  in Grid.h*/

		/*delete GameCells[cell_y][cell_x];*/ /* the old dynamic memory address is deleted so we can use the new operator to recreate a new type
										  at the same location that was clicked*/
		/*GameCells[cell_y][cell_x] = new EnemyCell(cell_y, cell_x);*/ // NB:since the row number is actually the y coordinate while column is x

		EnemyCell* pEnemyCell; //This pointer will be used to apply the set function in case of there will be future derived classes from the Grid class because the pointer "GameCells" is a private data member in the Grid class
		pEnemyCell = new EnemyCell(Enemy_Cell_y, Enemy_Cell_x); //The new operator is essential here because the cell coordinates are specified by the user during the runtime. 
		setCell(Enemy_Cell_y, Enemy_Cell_x, pEnemyCell); //The "setCell" function contains the delete operator so that it deletes the data pointed to it by the pointer "pEnemyCell" after setting the "GameCells" private data member

		pGUI->DrawCell(GameCells[Enemy_Cell_y][Enemy_Cell_x]);	/* we call the DrawCell function from GUI and give it the cell's pointer, it reads
													the row number columb number to locate it on the grid and identifies type of cell subtype
													and fetches the image path in the subcell derived class to paste the saved image in the
													cell*/
		
		pGUI->PrintMessage("Enemy Added");  // prints message to confirm that the swap was succesful
		break;  // we break out of the switch statement

////////////////////////////////////////////////////
	case OBSTACLE:

		pGUI->PrintMessage("Obstacle clicked");
		int Obstacle_x, Obstacle_y;
		pGUI->GetPointClicked(Obstacle_x,Obstacle_y); /* H... these x and y are passed by reference so that the funct*/
		Obstacle_Cell_x = Obstacle_x / 50;
		Obstacle_Cell_y = (Obstacle_y / 50) - 1;

		GridChecker(Obstacle_Cell_x, Obstacle_Cell_y);
		pGUI->PrintMessage("Obstacle Added");

		/*delete GameCells[Obstacle_Cell_y][Obstacle_Cell_x];
		GameCells[Obstacle_Cell_y][Obstacle_Cell_x] = new ObstacleCell(Obstacle_Cell_y, Obstacle_Cell_x); */

		ObstacleCell* pObstacleCell; //for explanation, refer to the comments in the case Enemy above.
		pObstacleCell = new ObstacleCell(Obstacle_Cell_y, Obstacle_Cell_x);
		setCell(Obstacle_Cell_y, Obstacle_Cell_x, pObstacleCell);

		pGUI->DrawCell(GameCells[Obstacle_Cell_y][Obstacle_Cell_x]);
		break;
///////////////////////////////////////////
	case EMPTYCELL:

		pGUI->PrintMessage("Empty Cell clicked");
		int Empty_x, Empty_y;
		pGUI->GetPointClicked(Empty_x, Empty_y); /* H... these x and y are passed by reference so that the funct*/
		Empty_Cell_x = Empty_x / 50;
		Empty_Cell_y = (Empty_y / 50) - 1;

		GridChecker(Empty_Cell_x, Empty_Cell_y);
		pGUI->PrintMessage("Empty Cell Added");

		/*delete GameCells[Empty_Cell_y][Empty_Cell_x];
		GameCells[Empty_Cell_y][Empty_Cell_x] = new EmptyCell(Empty_Cell_y, Empty_Cell_x);*/

		EmptyCell* pEmptyCell; //for explanation, refer to the comments in the case Enemy above.
		pEmptyCell = new EmptyCell(Empty_Cell_y, Empty_Cell_x);
		setCell(Empty_Cell_y, Empty_Cell_x, pEmptyCell);

		pGUI->DrawCell(GameCells[Empty_Cell_y][Empty_Cell_x]);
		
		break;

//////////////////////////////////////////
	case HEART:

		pGUI->PrintMessage("Heart Cell clicked");
		int Heart_x, Heart_y;
		pGUI->GetPointClicked(Heart_x, Heart_y); 
		Heart_Cell_x = Heart_x / 50;
		Heart_Cell_y = (Heart_y / 50) - 1;

		GridChecker(Heart_Cell_x, Heart_Cell_y);
		pGUI->PrintMessage("Heart Added");

		/*delete GameCells[Heart_Cell_y][Heart_Cell_x];
		GameCells[Heart_Cell_y][Heart_Cell_x] = new HeartCell(Heart_Cell_y, Heart_Cell_x);*/

		HeartCell* pHeartCell; //for explanation, refer to the comments in the case Enemy above.
		pHeartCell = new HeartCell(Heart_Cell_y, Heart_Cell_x);
		setCell(Heart_Cell_y, Heart_Cell_x, pHeartCell);

		pGUI->DrawCell(GameCells[Heart_Cell_y][Heart_Cell_x]);

		break;
//////////////////////////////////////////
	case WINGS:

		pGUI->PrintMessage("Wings Cell clicked");
		int Wings_x, Wings_y;
		pGUI->GetPointClicked(Wings_x, Wings_y);
		Wings_Cell_x = Wings_x / 50;
		Wings_Cell_y = (Wings_y / 50) - 1;

		GridChecker(Wings_Cell_x, Wings_Cell_y);
		pGUI->PrintMessage("Wings Added");

		/*delete GameCells[Wings_Cell_y][Wings_Cell_x];
		GameCells[Wings_Cell_y][Wings_Cell_x] = new WingsCell(Wings_Cell_y, Wings_Cell_x);*/

		WingsCell* pWingsCell; //for explanation, refer to the comments in the case Enemy above.
		pWingsCell = new WingsCell(Wings_Cell_y, Wings_Cell_x);
		setCell(Wings_Cell_y, Wings_Cell_x, pWingsCell);

		pGUI->DrawCell(GameCells[Wings_Cell_y][Wings_Cell_x]);

		break;
////////////////////////////////////////////
	case EGG:

		pGUI->PrintMessage("Egg Cell clicked");
		int Egg_x, Egg_y;
		pGUI->GetPointClicked(Egg_x, Egg_y);
		Egg_Cell_x = Egg_x / 50;
		Egg_Cell_y = (Egg_y / 50) - 1;

		GridChecker(Egg_Cell_x, Egg_Cell_y);
		pGUI->PrintMessage("Egg Added");

		/*delete GameCells[Egg_Cell_y][Egg_Cell_x];
		GameCells[Egg_Cell_y][Egg_Cell_x] = new EggCell(Egg_Cell_y, Egg_Cell_x);*/

		EggCell* pEggCell; //for explanation, refer to the comments in the case Enemy above.
		pEggCell = new EggCell(Egg_Cell_y, Egg_Cell_x);
		setCell(Egg_Cell_y, Egg_Cell_x, pEggCell);

		pGUI->DrawCell(GameCells[Egg_Cell_y][Egg_Cell_x]);

		break;
/////////////////////////////////////////////////
	case ARMOUR:

		pGUI->PrintMessage("Armour Cell clicked");
		int Armour_x, Armour_y;
		pGUI->GetPointClicked(Armour_x, Armour_y);
		Armour_Cell_x = Armour_x / 50;
		Armour_Cell_y = (Armour_y / 50) - 1;

		GridChecker(Armour_Cell_x, Armour_Cell_y);
		pGUI->PrintMessage("Armour Added");

		/*delete GameCells[Armour_Cell_y][Armour_Cell_x];
		GameCells[Armour_Cell_y][Armour_Cell_x] = new ArmourCell(Armour_Cell_y, Armour_Cell_x);*/

		ArmourCell* pArmourCell; //for explanation, refer to the comments in the case Enemy above.
		pArmourCell = new ArmourCell(Armour_Cell_y, Armour_Cell_x);
		setCell(Armour_Cell_y, Armour_Cell_x, pArmourCell);

		pGUI->DrawCell(GameCells[Armour_Cell_y][Armour_Cell_x]);

		break;
//////////////////////////////////////////////
	case GOAL:

		pGUI->PrintMessage("Goal Cell clicked");
		int Goal_x, Goal_y;
		pGUI->GetPointClicked(Goal_x, Goal_y);
		Goal_Cell_x = Goal_x / 50;
		Goal_Cell_y = (Goal_y / 50) - 1;

		GridChecker(Goal_Cell_x, Goal_Cell_y);
		pGUI->PrintMessage("Goal Added");

		/*delete GameCells[Goal_Cell_y][Goal_Cell_x];
		GameCells[Goal_Cell_y][Goal_Cell_x] = new GoalCell(Goal_Cell_y, Goal_Cell_x);*/

		GoalCell* pGoalCell; //for explanation, refer to the comments in the case Enemy above.
		pGoalCell = new GoalCell(Goal_Cell_y, Goal_Cell_x);
		setCell(Goal_Cell_y, Goal_Cell_x, pGoalCell);

		pGUI->DrawCell(GameCells[Goal_Cell_y][Goal_Cell_x]);

		break;
//////////////////////////////////////////////
	case BOMB:

		pGUI->PrintMessage("Bomb Cell clicked");
		int Bomb_x, Bomb_y;
		pGUI->GetPointClicked(Bomb_x, Bomb_y);
		Bomb_Cell_x = Bomb_x / 50;
		Bomb_Cell_y = (Bomb_y / 50) - 1;

		GridChecker(Bomb_Cell_x, Bomb_Cell_y);
		pGUI->PrintMessage("Bomb Added");

		/*delete GameCells[Bomb_Cell_y][Bomb_Cell_x];
		GameCells[Bomb_Cell_y][Bomb_Cell_x] = new BombCell(Bomb_Cell_y, Bomb_Cell_x);*/

		BombCell* pBombCell; //for explanation, refer to the comments in the case Enemy above.
		pBombCell = new BombCell(Bomb_Cell_y, Bomb_Cell_x);
		setCell(Bomb_Cell_y, Bomb_Cell_x, pBombCell);

		pGUI->DrawCell(GameCells[Bomb_Cell_y][Bomb_Cell_x]);

		break;
////////////////////////////////////////////////
	case FREEZER:

		pGUI->PrintMessage("Freezer Cell clicked");
		int Freezer_x, Freezer_y;
		pGUI->GetPointClicked(Freezer_x, Freezer_y);
		Freezer_Cell_x = Freezer_x / 50;
		Freezer_Cell_y = (Freezer_y / 50) - 1;

		GridChecker(Freezer_Cell_x, Freezer_Cell_y);
		pGUI->PrintMessage("Freezer Added");

		/*delete GameCells[Freezer_Cell_y][Freezer_Cell_x];
		GameCells[Freezer_Cell_y][Freezer_Cell_x] = new FreezerCell(Freezer_Cell_y, Freezer_Cell_x);*/

		FreezerCell* pFreezerCell; //for explanation, refer to the comments in the case Enemy above.
		pFreezerCell = new FreezerCell(Freezer_Cell_y, Freezer_Cell_x);
		setCell(Freezer_Cell_y, Freezer_Cell_x, pFreezerCell);

		pGUI->DrawCell(GameCells[Freezer_Cell_y][Freezer_Cell_x]);

		break;
////////////////////////////////////////////////
		/*pGUI->ClearCell*/

		// now to clear the empty cell from this x and y location


/////////////////////////////////////////////////////////////////////////////////////////
	///TODO: Add a case for EACH Action type
	case MOVE_UP:
	case MOVE_DOWN:
	case MOVE_RIGHT:
	case MOVE_LEFT:
		player->Move(this,ActType);
		break;		

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

}


Grid::~Grid()
{
	delete pGUI;
}

//////////////////////////////////////////////////////////////////////////////////


// Runs the application

void Grid::RunApp()
{
	/* H.....we will force the user to first select a position for the player by forcing them to click on the player 
	cell and placing it correctly*/
	int x, y;
	pGUI->PrintMessage("FIRST!!: PLEASE SELECT THE CHICKEN AND CLICK ON GRID TO SET STARTING POINT ");

	/*int PlayerCell_x, PlayerCell_y;*/
	pGUI->GetPointClicked(x, y);
	// H...limit clicks to the player cell ONLY, the game will stay pasued till they click it.
	while(!(y >= 0 && y < ToolBarHeight && x/50==4)) 
	{
		pGUI->PrintMessage("INVALID PLEASE SELECT THE PLAYER CELL-CHICKEN first");
		pGUI->GetPointClicked(x, y);		
	}

	// H...limit clicks to the grid otherwise it returns invalid in status bar
	pGUI->PrintMessage("Now please select the starting position in the grid"); 
	pGUI->GetPointClicked(x, y);
	int PlayerCell_x = x / 50;
	int PlayerCell_y = (y / 50) - 1;

	GridChecker(PlayerCell_x, PlayerCell_y); // checks for the validity of the click that it is within our Grid


	int row = PlayerCell_y, col=PlayerCell_x;	//H...here we set where we intend the player to start
	pGUI->ClearStatusBar();
	

	PlayerCell* pCell = new PlayerCell(row,col);  /* H.......here we create a pointer of the type PlayerCell, it will point to a  
	                                              fixed position in the dynamic memory that we create to store a playerCell type
												  and we initialize it with row and column in the argument, the ones we both declared
												  and initialized above*/

	setCell(row,col, pCell);       /* here we use the seCell function from this same GUI class above which deletes the dynamic memory at
								   row and col and recreates in the same position, a pointer of the type pCell we specified*/

	player = new Player(*pCell);	/*we then use the player class type pointer we created in the .h file and have it point to a 
									dynamic memory address of the type player and initialize it with the values that our pcel pointer
									references using the dereferencing operator* */
	pGUI->DrawCell(pCell);

	starter_x = col;  /* we save the player location so that we can use it to prevent further clicks on the fixed location using the 
					  function GridChecker i defined in Grid.h*/
	starter_y = row;
		
	while (1)
	{
		ActionType act = GetUserAction();
		if(act == EXIT)
			return;       //H... this ends the function early without executing the rest of the code
		
		ExecuteAction(act);
		
		Sleep(100);
	}

}

////////////////////////////////////////////////////////////////////////////////////
bool Grid::IsValidCell(int row, int col) const
{
	return (row >= 0 && row < NumRowCells) 
			&& (col >=0 && col < NumColumnCells);
}
/////////////////////////////////////////////////////////////////////////////////////
////////////////THE SAVE ALL FUNCTION////////////////////////////////////////////////

void Grid::save_all()
{
	pGUI->PrintMessage("Enter the file name to be saved: ");	
	
	string file_name = pGUI->GetSrting();

	//ofstream output_file(file_name.c_str());

	ofstream output_file;

	output_file.open(file_name.c_str());

	output_file << "Number of non empty cell: " << Cell::get_num_of_non_empty_cells() << endl;

	output_file << player->get_health() << " " << player->get_lives() << " " << player->get_score() << endl;
	
	for (int i = 0; i < NumRowCells; i++)
	{
		for (int j = 0; j < NumColumnCells; j++)
		{
			output_file << GameCells[i][j]->save() << " " << i << " " << j << endl;
		}
	}

	output_file.close();
	
}

void Grid::load()
{
	string file_name = pGUI->GetSrting();
	
	int temp, row, column; string mousa;

	ifstream input_file;

	input_file.open(file_name.c_str());

	getline(input_file, mousa);
	//pGUI->PrintMessage(mousa);
	
	input_file >> temp;

	cout << temp;
	player->set_health(temp);

	input_file >> temp;
	player->set_lives(temp);

	input_file >> temp;
	player->set_score(temp);

	//getline(input_file, mousa);

	while (!input_file.eof())
	{
		input_file >> mousa >> row >> column;

		if (mousa == "Empty")
		{
			EmptyCell(row, column);
		}
		else if (mousa == "Armour")
			ArmourCell(row, column);
		else if (mousa == "Heart")
			HeartCell(row, column);
		else if (mousa == "Bomb")
			BombCell(row, column);
		else if (mousa == "Egg")
			EggCell(row, column);
		else if (mousa == "Empty")
			EmptyCell(row, column);
		else if (mousa == "Enemy")
			EnemyCell(row, column);
		else if (mousa == "Freezer")
			FreezerCell(row, column);
		else if (mousa == "Goal")
			GoalCell(row, column);
		else if (mousa == "Obstacle")
			ObstacleCell(row, column);
		else if (mousa == "Player")
			PlayerCell(row, column);
		
	}

	input_file.close();

}