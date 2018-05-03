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
private:
	std::vector<InPort> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	std::vector<OutPort> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
protected:
	const BlockType type;
	BlockBase(Graph &g, BlockType type, std::string name);
	BlockBase(Graph &g, BlockType type, std::string name,
			  std::initializer_list<InPort> inputs,
			  std::initializer_list<OutPort> outputs);
public:
	Graph &graph;
	const std::string name;
	virtual InPort & Input(std::size_t id);
	virtual std::size_t InputCount();
	virtual OutPort & Output(std::size_t id);
	virtual std::size_t OutputCount();
	virtual bool HasAllValues();
	virtual bool InputsAreConnected();
	virtual bool Computable();
	virtual void Compute() = 0;
	virtual ~BlockBase() = default;
};

#endif // BLOCKBASE_H
