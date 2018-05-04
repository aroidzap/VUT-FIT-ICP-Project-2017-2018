/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: vectordotproductblock.cpp
*/

#include "vectordotproductblock.h"
#include "../types/types.h"
#include "../blocks.h"

VectorDotProductBlock::VectorDotProductBlock(Graph &g)
	: BlockBase(g, VECTOR_DOTPRODUCT, BLOCK_NAME.at(VECTOR_DOTPRODUCT),
    {
        InPort(*this, vec2(), "A"),
        InPort(*this, vec2(), "B")
    },
    {
		OutPort(*this, scal(), "Dot")
    }
    ){}

void VectorDotProductBlock::Compute()
{
	this->Output(0)["val"] = this->Input(0)["x"] * this->Input(1)["x"] + this->Input(0)["y"] * this->Input(1)["y"];
}
