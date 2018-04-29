#include "blockbase.h"

BlockBase::BlockBase(Graph &g, BlockType type, std::string name,
					 std::initializer_list<InPort> inputs,
					 std::initializer_list<OutPort> outputs)
 : graph(g), type(type), name(name), inputs(inputs), outputs(outputs) { }

bool BlockBase::HasAllValues()
{
	for (InPort &p : this->inputs) {
		if(p.Value().isNull()){
			return false;
		}
	}
	return true;
}
