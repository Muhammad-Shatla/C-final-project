#include "EmptyCell.h"


EmptyCell::EmptyCell(int row, int col):Cell(row,col)
{
	ImagePath = "images\\Cells\\EmptyCell.jpg";
}


string EmptyCell::save()
{
	return "Empty";
}

bool EmptyCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns true as it is NOT an obstacle cell
	return true;
}

EmptyCell::~EmptyCell(void)
{
}