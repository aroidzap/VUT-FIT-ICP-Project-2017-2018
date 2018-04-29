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

void Graph::addConnection(const OutPort &a, const InPort &b)
{
	connections.insert(std::pair<const InPort *, const OutPort *>(&b, &a));
}

void Graph::removeConnection(const OutPort &a, const InPort &b)
{
	//connections.erase(std::pair<const InPort *, const OutPort *>(&b, &a));
}
