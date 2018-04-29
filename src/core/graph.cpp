#include "graph.h"
#include <utility>

Graph::Graph(std::string name) : name(name) { }

Graph::Graph(std::string name, std::initializer_list<BlockBase*> blocks) : Graph(name)
{
	for(BlockBase *b : blocks){
		addBlock(b);
	}
}

void Graph::addBlock(BlockBase *b)
{
	this->blocks.push_back(b);
}

void Graph::removeBlock(BlockBase *b)
{
	this->blocks.remove(b);
}

void Graph::addConnection(const OutPort &a, const InPort &b)
{
	connections.insert(std::pair<const InPort *, const OutPort *>(&b, &a));
}

void Graph::removeConnection(const OutPort &a, const InPort &b)
{
	//connections.erase(std::pair<const InPort *, const OutPort *>(&b, &a));
}
