#pragma once
#include "Cell.h"
class ArmourCell :
	public Cell
{
public:
	ArmourCell(int row, int col);
	virtual bool ActOn(Player* p);
	string save();
	virtual~ArmourCell();
};

