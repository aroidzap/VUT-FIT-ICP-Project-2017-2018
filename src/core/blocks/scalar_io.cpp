/** ICP Project 2017/2018: BlockEditor
 * @file scalar_io.cpp
 * @brief Scalar IO block's operation and ports definition
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "scalar_io.h"
#include "../types/types.h"

ScalarInput::ScalarInput(Graph &g)
	: BlockBase(g, SCAL_INPUT, "Input",
{}, {OutPort(*this, scal(), "")}) { }

void ScalarInput::Compute() { }

ScalarOutput::ScalarOutput(Graph &g)
	: BlockBase(g, SCAL_OUTPUT, "Output",
	{InPort(*this, scal(), "")}, {}) { }

void ScalarOutput::Compute() { }
