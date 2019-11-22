#include "GUI.h"


GUI::GUI()
{

	// Colors

	MsgColor = DARKRED;		    // StatusBar Messages color
	BkGrndColor = DARKSLATEBLUE;	// Grid Background color
	StatusBarColor = GREY;       // StatusBar Background color

	GridLineColor = LIGHTGRAY;   // Vertical and Horizontal Lines
	ObstacleColor = BLACK;       // Background of Obstacles
	
	// Create the output window
	pWind = new window(WindWidth + 15, WindHeight, 5, 5); 

	// Change the title
	pWind->ChangeTitle("Game");
		
	CreateMenu();
	ClearGridArea();
	ClearStatusBar();

	InterfaceMode = MODE_MENU;
}


//window* GUI::CreateWind(int w, int h, int x, int y) const
//{ 
//	window* pW = new window(w, h, x, y);
//	/*pW->SetBrush(BkGrndColor);
//	pW->SetPen(BkGrndColor, 1);
//	pW->DrawRectangle(0, ToolBarHeight, w, h);	*/
//	return pW;
//}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(int &x, int &y, bool wait) const
{
	if(wait)
		pWind->WaitMouseClick(x, y); // wait (pause) till a mouse click
	else
		pWind->GetMouseClick(x, y);	 // no wait
}

////////////////////////////////////////////////////////////////////////////////////////// 

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if(Key == 13 )	// ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType GUI::GetUserAction() const
{	
	int x = -1, y = -1;
	

	//  ============ GUI in the MODE_MENU mode ============
	if ( InterfaceMode == MODE_MENU )	/*...H...remember we have either a game mode where clicks are disabled and you use ESC to
										pasue switching you to menu mode OR the menue mode where mouse clicks are recorded as actions*/
	{
		pWind->WaitMouseClick(x, y);
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)    // we set the range of the Y location above which the menu is identified.
		{	
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case ITM_START: 
				pWind->FlushKeyQueue();
				pWind->FlushMouseQueue();
				return START;

/////////////////////////////////////////////////////////

			case ITM_Enemy: return ENEMY;
			case ITM_Player: return PLAYER;
			case ITM_Obstacle: return OBSTACLE;
			case ITM_EmptyCell: return EMPTYCELL;
			case ITM_Heart: return HEART;
			case ITM_Wings: return WINGS;
			case ITM_Egg: return EGG;
			case ITM_Armour:return ARMOUR;
			case ITM_Bomb:return BOMB;
			case ITM_Freezer: return FREEZER;
			case ITM_Goal:return GOAL;

//////////////////////////////////////////////////////////

			case ITM_EXIT: return EXIT;

//////////////////////////////////////////////////////////
			///TODO: Add cases for the other items of Create-Grid Mode
			



			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ( (y >= ToolBarHeight) && (y < WindHeight - StatusBarHeight))
		{
			return GRID_AREA;	
		}

		// [3] User clicks on the status bar
		return STATUS;

//		// [4] user clicks on enemy in menue bar
//		if () {
//			
//			
//			
//;
//		}
	}
	// ============ GUI in the GAME mode ============
	else	
	{

		char keyData;
		keytype Ktype = pWind->GetKeyPress(keyData);

		if(Ktype == ESCAPE )    //H... if you press the ESCAPE key the game pauses. and exits the playmode
		{
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();
			return PAUSE;
		}
	
		if (Ktype == ARROW)		//move player using arrow keys
		switch(keyData)
		{
		case 2:	return MOVE_DOWN;
		case 4:	return MOVE_LEFT;
		case 6:	return MOVE_RIGHT;
		case 8:	return MOVE_UP;				
		}


		return NO_MOVE; // if other keys is pressed OR if it can't move because of obstacle

		///TODO:
		// perform more checks iof needed and return the corresponding ActionType
	}	

}


//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

GUI_MODE GUI::getInterfaceMode() const
{
	return InterfaceMode;
}


void GUI::setInterfaceMode(GUI_MODE mode) 
{
	InterfaceMode = mode;
}

////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearStatusBar() const
{
	// Clear Status bar by drawing a filled rectangle with status bar background color
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearGridArea() const
{
	/*
	// Create a big rectangle with the background of the Grid
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, WindWidth, WindHeight - StatusBarHeight);
	*/
	// Set the pen of the vertical and horizontal lines of the Grid
	pWind->SetPen(GridLineColor,1);
	int x1, y1, x2, y2;

	// Draw Vertical Lines
	y1 = ToolBarHeight;
	y2 = WindHeight - StatusBarHeight;
	for (int i = 0; i < NumColumnCells; i++)
	{
		x1 = x2 = i * GridCellWidth; 
		pWind->DrawLine(x1, y1, x2, y2);
	}	
	
	// Draw Horizontal Lines
	x1 = 0;
	x2 = WindWidth;
	for (int i = 0; i < NumRowCells; i++) 
	{
		y1 = y2 = ToolBarHeight + i * GridCellWidth; 
		pWind->DrawLine(x1, y1, x2, y2);
	}	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateMenu() 
{
	InterfaceMode = MODE_MENU;

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way
	
	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum MENU_ITEMS
	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[ITM_START] = "images\\MenuItems\\Start.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit.jpg";
	MenuItemImages[ITM_Enemy] = "images\\Cells\\EnemyCell.jpg";
	MenuItemImages[ITM_Player] = "images\\Cells\\PlayerCell.jpg";
	MenuItemImages[ITM_Obstacle] = "images\\Cells\\ObstacleCell.jpg";
	MenuItemImages[ITM_EmptyCell] = "images\\Cells\\EmptyCell.jpg";
	MenuItemImages[ITM_Heart] = "images\\Cells\\Heart.jpg";
	MenuItemImages[ITM_Wings] = "images\\Cells\\Wings.jpg";
	MenuItemImages[ITM_Egg] = "images\\Cells\\Egg.jpg";
	MenuItemImages[ITM_Armour] = "images\\Cells\\Armour.jpg";
	MenuItemImages[ITM_Bomb] = "images\\Cells\\Bomb.jpg";
	MenuItemImages[ITM_Freezer] = "images\\Cells\\Freezer.jpg";
	MenuItemImages[ITM_Goal] = "images\\Cells\\GoalCell.jpg";

	///TODO: Prepare images for each menu item and add it to the list

	// Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);

	// Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, WindWidth, ToolBarHeight);	

}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(18, BOLD , BY_NAME, "Verdana");   
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight/1.3), msg);
}

//======================================================================================//
//						Game Objects Drawing Functions   								//
//======================================================================================//

void GUI::DrawCell(const Cell * cell) const
{
	pWind->SetPen(ObstacleColor, 1);
	pWind->SetBrush(ObstacleColor);
	drawstyle style = FILLED;	

	int x = cell->getCol() * GridCellWidth;
	int y = ToolBarHeight + ( cell->getRow() * GridCellWidth );
	pWind->DrawImage(cell->getImage(),x+1, y+1, GridCellWidth-1, GridCellWidth-1) ;  /*H... the DrawImage function gets and scales the image
																					 to the cell size 50x50 specified in the grid it takes
																					 arguments for the image path, the location of the start
																					 of the image's left edge+1 (to leave a 1x and 1y wide
																					 white line for the gridlines) then the width and height
																					 of the image which is to be scalled accordingly into a 
																					 48x48 square image taking off 1 unit form left, right,
																					 top and bot for the white lines*/
}

//////////////////////////////////////////////////////////////////////////////////////////


//void GUI::ClearCell(const Cell & cell) const
//{
//	pWind->SetPen(GridLineColor, 1);
//	pWind->SetBrush(BkGrndColor);
//	int x1, y1, x2, y2;
//	x1 = cell.getCol() * GridCellWidth;
//	y1 = ToolBarHeight + ( cell.getRow() * GridCellWidth );
//	x2 = x1 + GridCellWidth;
//	y2 = y1 + GridCellWidth;
//	pWind->DrawRectangle(x1, y1, x2+1, y2+1);
//}

//////////////////////////////////////////////////////////////////////////////////////////




GUI::~GUI()  //H.... the deconstructor deletes the allocated dynamic memory when the GUI object is killed on exit
{
	delete pWind;
}
