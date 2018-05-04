/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalaraddblock.h
*/

#ifndef SCALARADDBLOCK
#define SCALARADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

class ScalarAddBlock : public BlockBase
{
public:
    ScalarAddBlock(Graph &g);
    void Compute() override;
    virtual ~ScalarAddBlock() = default;
};

#endif // SCALARADDBLOCK

