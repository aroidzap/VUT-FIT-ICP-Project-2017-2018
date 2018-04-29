#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <string>
#include <vector>
#include <initializer_list>
#include "port.h"

enum BlockType {
	VECTOR_ADD = 0,
	VECTOR_SUB = 1,
	SCALAR_ADD = 2,
	SCALAR_SUB = 3,
	VEC_SCAL_MULTIPLY = 4
};

class BlockBase {
public: //TODO: protected
	const BlockType type;
	const std::string name;
	std::vector<InPort> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	std::vector<OutPort> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	BlockBase(BlockType type, std::string name,
			  std::initializer_list<InPort> inputs,
			  std::initializer_list<OutPort> outputs);
public:
	bool HasAllValues() const;
	virtual void Compute() = 0;
};

class BlockBaseID : public BlockBase {
private:
	const int id;
public:
	BlockBaseID(BlockBase &b, int id);
	const int getId() const;
};

#endif // BLOCKBASE_H
