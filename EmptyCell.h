#pragma once
#include "cell.h"
class EmptyCell :
	public Cell
{
public:
	EmptyCell(int row, int col);
	
	string save();
	
	virtual ~EmptyCell();

	virtual bool ActOn(Player* p);
};

