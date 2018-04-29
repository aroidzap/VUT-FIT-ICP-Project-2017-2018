#include "graph.h"

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
