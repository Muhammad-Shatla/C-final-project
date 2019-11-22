#include "EggCell.h"



EggCell::EggCell(int row, int col) :Cell(row, col)
{
	ImagePath = "images\\Cells\\Egg.jpg";
	set_up_num_of_non_empty_cells();
}


string EggCell::save()
{
	return "Egg";
}

bool EggCell::ActOn(Player* p)
{
	// Still to be determined !!!
	return false;
}

EggCell::~EggCell()
{
	set_down_num_of_non_empty_cells();

}
