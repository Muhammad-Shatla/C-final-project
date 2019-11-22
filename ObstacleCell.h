#pragma once
#include "Cell.h"
class ObstacleCell :
	public Cell
{
public:
	ObstacleCell(int row, int col);
	
	string save();

	virtual bool ActOn(Player* p);

	virtual ~ObstacleCell();
};

