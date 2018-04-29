#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <string>
#include <vector>
#include <initializer_list>
#include "port.h"
#include "graph.h"
#include "blocks.h"

class Graph;

class BlockBase {
protected:
	const BlockType type;
	const std::string name;
	BlockBase(Graph &g, BlockType type, std::string name,
			  std::initializer_list<InPort> inputs,
			  std::initializer_list<OutPort> outputs);
public:
	Graph &graph;
	std::vector<InPort> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	std::vector<OutPort> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	bool HasAllValues();
	virtual void Compute() = 0;
};

#endif // BLOCKBASE_H
