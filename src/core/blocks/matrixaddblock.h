/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: matrixaddblock.h
*/

#ifndef MATRIXADDBLOCK
#define MATRIXADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

class MatrixAddBlock : public BlockBase
{
public:
    MatrixAddBlock(Graph &g);
    void Compute() override;
    virtual ~MatrixAddBlock() = default;
};

#endif // MATRIXADDBLOCK

