#pragma once
#include "Cell.h"
class WeaponCell :
	public Cell
{
public:
	WeaponCell(int row, int col);

	virtual bool ActOn(Player* p);

	virtual~WeaponCell();
};

