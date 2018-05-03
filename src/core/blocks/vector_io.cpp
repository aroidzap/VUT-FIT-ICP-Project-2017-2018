#include "vector_io.h"
#include "../types/types.h"

VectorInput::VectorInput(Graph &g)
	: BlockBase(g, VECTOR_INPUT, "Vector",
{}, {OutPort(*this, vec2(), "")}) { }

void VectorInput::Compute() { }

VectorOutput::VectorOutput(Graph &g)
	: BlockBase(g, VECTOR_OUTPUT, "Vector",
	{InPort(*this, vec2(), "")}, {}) { }

void VectorOutput::Compute() { }
