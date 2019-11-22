#pragma once
#include "Cell.h"
class HeartCell :
	public Cell
{
public:
	HeartCell(int row, int col);

	string save();

	virtual bool ActOn(Player* p);

	virtual~HeartCell();
};

