#include "vectoraddblock.h"
#include "../types/types.h"

VectorAddBlock::VectorAddBlock(Graph &g)
	: BlockBase(g, VECTOR_ADD, "Vector Add",
	{
		InPort(*this, vec2(), "A"),
		InPort(*this, vec2(), "B")
	},
	{
		OutPort(*this, vec2(), "Out")
	}
	){}

void VectorAddBlock::Compute()
{
	this->Output(0)["x"] = this->Input(0)["x"] + this->Input(1)["x"];
	this->Output(0)["y"] = this->Input(0)["y"] + this->Input(1)["y"];
}
