/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: matrixmulblock.h;
*/

#ifndef MATRIXMULBLOCK
#define MATRIXMULBLOCK

#include "../blockbase.h"
#include "../graph.h"

class MatrixMulBlock : public BlockBase
{
public:
    MatrixMulBlock(Graph &g);
    void Compute() override;
    virtual ~MatrixMulBlock() = default;
};

#endif // MATRIXMULBLOCK

