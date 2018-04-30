#include "graph.h"
#include <utility>

Graph::Graph() : bf(*this) { }

void Graph::SetName(const std::string name)
{
	this->name = name;
}

BlockFactory &Graph::GetBlockFactory()
{
	return bf;
}

void Graph::addBlock(BlockType t)
{
	this->blocks.push_back(GetBlockFactory().AllocBlock(t));
}

void Graph::removeBlock(BlockBase *b)
{
	this->blocks.remove(b);
	GetBlockFactory().FreeBlock(b);
}

void Graph::addConnection(OutPort &a, InPort &b)
{
	connections.insert(std::pair<InPort *, OutPort *>(&b, &a));
}

void Graph::removeConnection(OutPort &a, InPort &b)
{
	if ((connections.find(&b) != connections.end()) &&
		(connections.at(&b) == &a)) {
		connections.erase(&b);
	}
}

void Graph::removeConnection(InPort &p)
{
	connections.erase(&p);
}
