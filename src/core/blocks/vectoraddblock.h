#ifndef VECTORADDBLOCK_H
#define VECTORADDBLOCK_H

#include "../blockbase.h"

class VectorAddBlock : public BlockBase
{
public:
	VectorAddBlock();
	void Compute() override;
};

#endif // VECTORADDBLOCK_H
