#include "vectoraddblock.h"
#include "../types/types.h"

VectorAddBlock::VectorAddBlock()
	: BlockBase(VECTOR_ADD, "Vector Add",
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
	this->outputs[0]["x"] = this->inputs[0]["x"] + this->inputs[1]["x"];
	this->outputs[0]["y"] = this->inputs[0]["y"] + this->inputs[1]["y"];
}
