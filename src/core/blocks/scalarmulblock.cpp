/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalarmulblock.cpp
*/

#include "scalarmulblock.h"
#include "../types/types.h"
#include "../blocks.h"

ScalarMulBlock::ScalarMulBlock(Graph &g)
	: BlockBase(g, SCALAR_MUL, BLOCK_NAME.at(SCALAR_MUL),
    {
        InPort(*this, scal(), "A"),
        InPort(*this, scal(), "B")
    },
    {
        OutPort(*this, scal(), "Out")
    }
    ){}

void ScalarMulBlock::Compute()
{
    this->Output(0)["val"] = this->Input(0)["val"] * this->Input(1)["val"];
}

