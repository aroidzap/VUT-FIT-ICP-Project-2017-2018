#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include "xml.h"
#include "port.h"
#include "blockbase.h"
#include "blockfactory.h"

class Graph
{
public: //TODO: private
	BlockFactory bf;
	std::string name;
	std::vector<BlockBase*> blocks;
	std::map<const InPort *, const OutPort *> connections;
public:
	Graph(const XML & xml);
	Graph(std::string name);
	Graph(std::string name, std::initializer_list<BlockType> blocks);
	const XML & saveGraph();

	void addBlock(BlockType);
	void removeBlock(BlockBase *b);
	void addConnection(const OutPort &a, const InPort &b);
	void removeConnection(const OutPort &a, const InPort &b);
	void computeReset();
	void computeStep();
	void computeAll();

};

#endif // GRAPH_H
