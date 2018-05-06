/** ICP Project 2017/2018: BlockEditor
 * @file vectordotproduct.cpp
 * @brief Vector dot product block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
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
