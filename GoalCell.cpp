#include "GoalCell.h"



GoalCell::GoalCell(int row, int col) :Cell(row, col)
{
	ImagePath = "images\\Cells\\GoalCell.jpg";
	set_up_num_of_non_empty_cells();
}


string GoalCell::save()
{
	return "Goal";
}


bool GoalCell::ActOn(Player* p)
{
	// Still to be determined !!!
	return false;
}


GoalCell::~GoalCell()
{
	set_down_num_of_non_empty_cells();
}
