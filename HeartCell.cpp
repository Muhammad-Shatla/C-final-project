#include "HeartCell.h"



HeartCell::HeartCell(int row, int col) :Cell(row, col)
{
	ImagePath = "images\\Cells\\Heart.jpg";
	set_up_num_of_non_empty_cells();
}

string HeartCell::save()
{
	return "Heart";
}


bool HeartCell::ActOn(Player* p)
{
	// Still to be determined !!!
	return false;
}


HeartCell::~HeartCell()
{
	set_down_num_of_non_empty_cells();
}
