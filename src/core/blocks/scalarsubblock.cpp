/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalarsubblock.cpp
*/

#include "scalarsubblock.h"
#include "../types/types.h"
#include "../blocks.h"

ScalarSubBlock::ScalarSubBlock(Graph &g)
	: BlockBase(g, SCALAR_SUB, BLOCK_NAME.at(SCALAR_SUB),
    {
        InPort(*this, scal(), "A"),
        InPort(*this, scal(), "B")
    },
    {
        OutPort(*this, scal(), "Out")
    }
    ){}

void ScalarSubBlock::Compute()
{
    this->Output(0)["val"] = this->Input(0)["val"] - this->Input(1)["val"];
}

