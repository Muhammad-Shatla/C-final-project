#include "ObstacleCell.h"



ObstacleCell::ObstacleCell(int row, int col):Cell(row,col)
{
	ImagePath = "images\\Cells\\ObstacleCell.jpg";
	set_up_num_of_non_empty_cells();
}


string ObstacleCell::save()
{
	return "Obstacle";
}


bool ObstacleCell::ActOn(Player* p)
{
	//Obstacle cell will prevent the player from crossing it
	//it returns False as it is an obstacle cell
	return false;
}

ObstacleCell::~ObstacleCell()
{
	set_down_num_of_non_empty_cells();
}
