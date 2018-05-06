/** ICP Project 2017/2018: BlockEditor
 * @file matrix_io.cpp
 * @brief Matrix IO block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
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
