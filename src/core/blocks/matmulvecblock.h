/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: matmulvecblock.h
*/

#ifndef MATMULVECBLOCK_H
#define MATMULVECBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

class MatMulVecBlock : public BlockBase
{
public:
	MatMulVecBlock(Graph &g);
	void Compute() override;
	virtual ~MatMulVecBlock() = default;
};

#endif // MATMULVECBLOCK_H
