/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: scalar_io.cpp
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
