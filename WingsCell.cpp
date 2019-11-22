#include "WingsCell.h"



WingsCell::WingsCell(int row, int col) :Cell(row, col)
{
	ImagePath = "images\\Cells\\Wings.jpg";
	set_up_num_of_non_empty_cells();
}


string WingsCell::save()
{
	return "Wings";
}


bool WingsCell::ActOn(Player* p)
{
	// Still to be determined !!!
	return false;
}

WingsCell::~WingsCell()
{
	set_down_num_of_non_empty_cells();
}
