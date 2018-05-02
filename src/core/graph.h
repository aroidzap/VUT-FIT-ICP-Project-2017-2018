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
#include "blockfactory.h"

class Graph
{
private:
	BlockFactory bf;
protected:
	std::string name;
	virtual BlockFactory & GetBlockFactory();
public:
	std::list<BlockBase*> blocks;
	std::map<InPort *, OutPort *> connections;

	Graph();

	virtual void SetName(const std::string name);

	void loadGraph(const XML & xml);
	const XML & saveGraph();

	void addBlock(BlockType);
	void removeBlock(BlockBase *b);
	OutPort * getConnectedOutPort(InPort &p);
	virtual bool addConnection(OutPort &a, InPort &b);
	virtual void removeConnection(OutPort &a, InPort &b);
	virtual void removeConnection(InPort &p);
	void computeReset();
	void computeStep();
	void computeAll();

};

#endif // GRAPH_H
