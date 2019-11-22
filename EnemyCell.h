#pragma once
#include "Cell.h"
class EnemyCell :
	public Cell
{
public:
	   	 
	EnemyCell(int row,int col);
	
	string save();
	
	virtual ~EnemyCell();

	virtual bool ActOn(Player* p);
};

