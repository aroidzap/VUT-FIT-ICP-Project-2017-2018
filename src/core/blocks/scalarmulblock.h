/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalarmulblock.h
*/

#ifndef SCALARMULBLOCK_H
#define SCALARMULBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

class ScalarMulBlock : public BlockBase
{
public:
    ScalarMulBlock(Graph &g);
    void Compute() override;
    virtual ~ScalarMulBlock() = default;
};

#endif // SCALARMULBLOCK_H

