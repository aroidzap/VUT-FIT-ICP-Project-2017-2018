#include "blockbase.h"

BlockBase::BlockBase(Graph &g, BlockType type, std::string name)
	: graph(g), type(type), name(name) { }

BlockBase::BlockBase(Graph &g, BlockType type, std::string name,
					 std::initializer_list<InPort> inputs,
					 std::initializer_list<OutPort> outputs)
 : graph(g), type(type), name(name), inputs(inputs), outputs(outputs) { }

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

bool BlockBase::HasAllValues()
{
	for (InPort &p : this->inputs) {
		if(p.Value().isNull()){
			return false;
		}
	}
	return true;
}

bool BlockBase::InputsAreConnected()
{
	for (InPort &p : this->inputs) {
		if(graph.connections.count(&p) <= 0) {
			return false;
		}
	}
	return true;
}

bool BlockBase::Computable()
{
	return true;
}
