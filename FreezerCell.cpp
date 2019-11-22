#include "FreezerCell.h"



FreezerCell::FreezerCell(int row, int col) :WeaponCell(row, col)
{
	ImagePath = "images\\Cells\\Freezer.jpg";
	set_up_num_of_non_empty_cells();
}

string FreezerCell::save()
{
	return "Freezer";
}


bool FreezerCell::ActOn(Player* p)
{
	//Still undefined
	return false;
}

FreezerCell::~FreezerCell()
{
	set_down_num_of_non_empty_cells();
}
