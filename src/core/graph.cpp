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

OutPort *Graph::getConnectedOutPort(InPort &p)
{
	if (connections.find(&p) != connections.end()){
		return connections.at(&p);
	} else {
		return nullptr;
	}
}

bool Graph::addConnection(OutPort &a, InPort &b)
{
	if(!a.Value().type_of(b.Value())) {
		return false;
	}
	//TODO: check acyclic
	connections.insert(std::pair<InPort *, OutPort *>(&b, &a));
	return true;
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
