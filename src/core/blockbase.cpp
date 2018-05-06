/** ICP Project 2017/2018: BlockEditor
 * @file blockbase.cpp
 * @brief Base class for blocks
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "blockbase.h"

BlockBase::BlockBase(Graph &g, BlockType type, std::string name)
	: graph(g), type(type), name(name) { }

BlockBase::BlockBase(Graph &g, BlockType type, std::string name,
					 std::initializer_list<InPort> inputs,
					 std::initializer_list<OutPort> outputs)
	: inputs(inputs), outputs(outputs), graph(g), type(type), name(name) { }

int BlockBase::getID() const
{
	return this->graph.getBlockID(*this);
}

int BlockBase::getPortID(const InPort &port) const
{
	int idx = 0;
	for (const InPort &p : inputs) {
		if (&p == &port){
			return idx;
		}
		idx++;
	}
	return -1;
}

int BlockBase::getPortID(const OutPort &port) const
{
	int idx = 0;
	for (const OutPort &p : outputs) {
		if (&p == &port){
			return idx;
		}
		idx++;
	}
	return -1;
}

InPort &BlockBase::Input(std::size_t id)
{
	return inputs[id];
}

std::size_t BlockBase::InputCount()
{
	return inputs.size();
}

OutPort &BlockBase::Output(std::size_t id)
{
	return outputs[id];
}

std::size_t BlockBase::OutputCount()
{
	return outputs.size();
}

void BlockBase::Reset()
{
	for(size_t i = 0; i < OutputCount(); i++) {
		Output(i).Value().setNull();
	}
}

bool BlockBase::HasAllValues()
{
	for(size_t i = 0; i < InputCount(); i++) {
		if (Input(i).Value().isNull()) {
			return false;
		}
	}
	return true;
}

bool BlockBase::InputsAreConnected()
{
	for(size_t i = 0; i < InputCount(); i++) {
		if(graph.connections.count(&Input(i)) <= 0) {
			return false;
		}
	}
	return true;
}

bool BlockBase::Computable()
{
	return true;
}
