#include "blockbase.h"

BlockBase::BlockBase(Graph &g, BlockType type, std::string name,
					 std::initializer_list<InPort> inputs,
					 std::initializer_list<OutPort> outputs)
 : graph(g), type(type), name(name), inputs(inputs), outputs(outputs) { }

bool BlockBase::HasAllValues() const
{
	for (const auto &p : this->inputs) {
		if(!p.HasValue()){
			return false;
		}
	}
	return true;
}
