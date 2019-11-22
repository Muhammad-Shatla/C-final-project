#pragma once
#include "cell.h"
class PlayerCell :	public Cell
{
public:
	PlayerCell(int row, int col);

	string save();

	virtual ~PlayerCell();

	virtual bool ActOn(Player* p);
};

