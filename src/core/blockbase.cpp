#include "blockbase.h"

BlockBase::BlockBase(BlockType type, std::string name,
					 std::initializer_list<InPort> inputs,
					 std::initializer_list<OutPort> outputs)
 : type(type), name(name), inputs(inputs), outputs(outputs) { }

bool BlockBase::HasAllValues() const
{
	for (const auto &p : this->inputs) {
		if(!p.HasValue()){
			return false;
		}
	}
	return true;
}

BlockBaseID::BlockBaseID(BlockBase &b, int id) : BlockBase(b), id(id) { }
