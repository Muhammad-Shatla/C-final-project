#pragma once
#include "Cell.h"
class GoalCell :
	public Cell
{
public:
	GoalCell(int row, int col);

	string save();

	virtual bool ActOn(Player* p);
	virtual~GoalCell();
};

