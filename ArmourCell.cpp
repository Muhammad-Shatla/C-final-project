#include "ArmourCell.h"



ArmourCell::ArmourCell(int row, int col) :Cell(row, col)

{
	ImagePath = "images\\Cells\\Armour.jpg";
	set_up_num_of_non_empty_cells();
}


bool ArmourCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns true as it is NOT an obstacle cell
	return true;
}

string ArmourCell::save()
{
	return "Armour";
}

ArmourCell::~ArmourCell()
{
	set_down_num_of_non_empty_cells();
}
