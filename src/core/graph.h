#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <initializer_list>
#include "xml.h"
#include "port.h"
#include "blockbase.h"

class Graph
{
protected:
	std::string name;
	std::list<BlockBase*> blocks;
	std::map<const InPort *, const OutPort *> connections;
public:
	Graph(const XML & xml);
	Graph(std::string name);
	Graph(std::string name, std::initializer_list<BlockBase*> blocks);
	const XML & saveGraph();

	void addBlock(BlockBase *b);
	void removeBlock(BlockBase *b);
	void addConnection(const OutPort &a, const InPort &b);
	void removeConnection(const OutPort &a, const InPort &b);
	void computeReset();
	void computeStep();
	void computeAll();

};

#endif // GRAPH_H
