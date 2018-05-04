/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalaraddblock.cpp
*/

#include "scalaraddblock.h"
#include "../types/types.h"
#include "../blocks.h"

ScalarAddBlock::ScalarAddBlock(Graph &g)
	: BlockBase(g, SCALAR_ADD, BLOCK_NAME.at(SCALAR_ADD),
    {
        InPort(*this, scal(), "A"),
        InPort(*this, scal(), "B")
    },
    {
        OutPort(*this, scal(), "Out")
    }
    ){}

void ScalarAddBlock::Compute()
{
    this->Output(0)["val"] = this->Input(0)["val"] + this->Input(1)["val"];
}
