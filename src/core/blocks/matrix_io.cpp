/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: matrix_io.cpp
*/

#include "matrix_io.h"
#include "../types/types.h"

MatrixInput::MatrixInput(Graph &g)
	: BlockBase(g, MAT2_INPUT, "Input",
{}, {OutPort(*this, mat2(), "")}) { }

void MatrixInput::Compute() { }

MatrixOutput::MatrixOutput(Graph &g)
	: BlockBase(g, MAT2_OUTPUT, "Output",
	{InPort(*this, mat2(), "")}, {}) { }

void MatrixOutput::Compute() { }
