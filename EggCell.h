
#include "Cell.h"
class EggCell :
	public Cell
{
public:
	EggCell(int row, int col);

	string save();


	virtual bool ActOn(Player* p);
	virtual~EggCell();
};
