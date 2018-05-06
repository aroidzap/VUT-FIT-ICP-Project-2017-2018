/** ICP Project 2017/2018: BlockEditor
 * @file vector_io.cpp
 * @brief Vector IO block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

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
