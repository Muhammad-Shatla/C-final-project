#include "BombCell.h"



BombCell::BombCell(int row, int col) :WeaponCell(row, col)
{
	ImagePath = "images\\Cells\\Bomb.jpg";
	set_up_num_of_non_empty_cells();
}

string BombCell::save()
{
	return "Bomb";
}

bool BombCell::ActOn(Player* p)
{
	//Still undefined
	return false;
}
BombCell::~BombCell()
{
	set_down_num_of_non_empty_cells();

}
