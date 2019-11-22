#include "EnemyCell.h"



EnemyCell::EnemyCell(int row,int col):Cell(row,col)
{
	ImagePath = "images\\Cells\\EnemyCell.jpg";
	set_up_num_of_non_empty_cells();
}


string EnemyCell::save()
{
	return "Enemy";
}


EnemyCell::~EnemyCell()
{
	set_down_num_of_non_empty_cells();
}

bool EnemyCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns false as it IS a kind of obstacle cell
	return false;
}