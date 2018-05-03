#include "vector_io.h"
#include "../types/types.h"

VectorInput::VectorInput(Graph &g)
	: BlockBase(g, VECTOR_INPUT, "Input",
{}, {OutPort(*this, vec2(), "")}) { }

void VectorInput::Compute() { }

VectorOutput::VectorOutput(Graph &g)
	: BlockBase(g, VECTOR_OUTPUT, "Output",
	{InPort(*this, vec2(), "")}, {}) { }

void VectorOutput::Compute() { }
