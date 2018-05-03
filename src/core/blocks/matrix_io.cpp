#include "matrix_io.h"
#include "../types/types.h"

MatrixInput::MatrixInput(Graph &g)
	: BlockBase(g, VECTOR_INPUT, "Input",
{}, {OutPort(*this, mat2(), "")}) { }

void MatrixInput::Compute() { }

MatrixOutput::MatrixOutput(Graph &g)
	: BlockBase(g, VECTOR_OUTPUT, "Output",
	{InPort(*this, mat2(), "")}, {}) { }

void MatrixOutput::Compute() { }
