#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <string>
#include <vector>
#include "port.h"

enum BlockType {
	VECTOR_ADD = 0,
	VECTOR_SUB = 1,
	SCALAR_ADD = 2,
	SCALAR_SUB = 3,
	VEC_SCAL_MULTIPLY = 4
};

class BlockBase {
protected:
	const BlockType type;
	const std::string name;
	const std::vector<InPort> inputs;
	const std::vector<OutPort> outputs;
	BlockBase(BlockType type, std::string name);
public:
	bool HasAllValues() const;
	virtual void Compute() = 0;
};

#endif // BLOCKBASE_H
