#pragma once
#include "WeaponCell.h"
class FreezerCell :
	public WeaponCell
{
public:
	FreezerCell(int row, int col);

	string save();

	virtual ~FreezerCell();
	virtual bool ActOn(Player* p);

};

