#include "PlayerCell.h"


PlayerCell::PlayerCell(int row, int col):Cell(row,col)
{
	ImagePath = "images\\Cells\\PlayerCell.jpg";
	set_up_num_of_non_empty_cells();
}


string PlayerCell::save()
{
	return "Player";
}


PlayerCell::~PlayerCell()
{
	set_down_num_of_non_empty_cells();
}


bool PlayerCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns true as it is NOT an obstacle cell
	return true;
}


