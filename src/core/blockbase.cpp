#include "blockbase.h"

BlockBase::BlockBase(BlockType type, std::string name) : type(type), name(name) { }

bool BlockBase::HasAllValues() const
{
	for (const auto &p : this->inputs) {
		if(!p.HasValue()){
			return false;
		}
	}
	return true;
}
