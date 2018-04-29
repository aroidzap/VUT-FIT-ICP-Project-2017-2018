#include "graph.h"
#include <utility>

Graph::Graph(std::string name) : name(name), bf(*this) { }

Graph::Graph(std::string name, std::initializer_list<BlockType> blocks) : Graph(name)
{
	for(auto b : blocks){
		addBlock(b);
	}
}

void Graph::addBlock(BlockType t)
{
	this->blocks.push_back(bf.AllocBlock(t));
}

void Graph::removeBlock(BlockBase *b)
{
	//this->blocks.remove(b);
	//bf.FreeBlock(b);
}

void Graph::addConnection(OutPort &a, InPort &b)
{
	connections.insert(std::pair<InPort *, OutPort *>(&b, &a));
}

void Graph::removeConnection(OutPort &a, InPort &b)
{
	//connections.erase(std::pair<const InPort *, const OutPort *>(&b, &a));
}
