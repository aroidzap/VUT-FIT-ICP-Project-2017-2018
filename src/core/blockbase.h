/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: blockbase.h
*/

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
	BlockBase(Graph &g, BlockType type, std::string name);
	BlockBase(Graph &g, BlockType type, std::string name,
			  std::initializer_list<InPort> inputs,
			  std::initializer_list<OutPort> outputs);
public:
	Graph &graph;
	const BlockType type;
	const std::string name;
	int getID() const;
	virtual int getPortID(const InPort &port) const;
	virtual int getPortID(const OutPort &port) const;
	virtual InPort & Input(std::size_t id);
	virtual std::size_t InputCount();
	virtual OutPort & Output(std::size_t id);
	virtual std::size_t OutputCount();
	bool HasAllValues();
	bool InputsAreConnected();
	virtual bool Computable();
	void Reset();
	virtual void Compute() = 0;
	virtual ~BlockBase() = default;
};

#endif // BLOCKBASE_H
