#pragma once

#include "GUI.h"
#include "DEFS.h"
#include "Cell.h"
class Player;	//forward class declaration

class Grid
{
	GUI * pGUI;   // a pointer to the the interface
	Cell*	GameCells[NumRowCells][NumColumnCells];	// Array of Pointers to Cell
	Player* player;
	int starter_x, starter_y;  // we will use these 2 variables to store the layer position to protect it from being erased.

public:

	Grid();	  

	// ========== Action-Related Functions ==========

	ActionType GetUserAction() const; // Reads the input command from the user and returns the corresponding action type

	void ExecuteAction(ActionType) ;  // Creates an action of the passed actionType and executes it

	void setCell(int r, int c, Cell* pCell);	//updates cell r,c to hold the new pointer pCell
	
	bool MoveIfPossible(Cell * pCurrentCell, ActionType dir); // Moves the entered position in the passed direction if no obstacles
	                                                       // updates currentCell if move takes place
	                                                       // Note: It returns bool indicating if a move occured or not

	bool IsValidCell(int r, int c) const;

	void DrawAllCells() const; // Draws the Grid and All its GameObjects


	GUI * getGUI() const;	// Gets a Pointer to the GUI

//////////////////////////////////My extra functions//////////////////////////////////////////////////////

	void save_all();

	void load();


	void GridChecker(int &cell_x, int &cell_y)/* a function we defined to check for the validity of the click, it should nither be on
												on the player cell or the status or menu bar, if you missclick you will get an error message
												 asking you to click within the grid and will prompt you for another click*/
	{	
		
		while ((!(cell_x <= 21 && cell_x >= 0 && cell_y >= 0 && cell_y <= 10)) || (cell_x==starter_x && cell_y==starter_y))
		{
			int x=0, y=0;			
			pGUI->PrintMessage("INVALID Please select a position inside the Grid - Blue area");
			pGUI->GetPointClicked(x,y);
			cell_x = x / 50;
			cell_y = (y / 50) - 1;
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	~Grid();
	void RunApp();	//Runs the application
};

