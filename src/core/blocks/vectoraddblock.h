#ifndef VECTORADDBLOCK_H
#define VECTORADDBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

class VectorAddBlock : public BlockBase
{
public:
	VectorAddBlock(Graph &g);
	void Compute() override;
};

#endif // VECTORADDBLOCK_H
