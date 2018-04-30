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
	if ((connections.find(&b) != connections.end()) &&
		(connections.at(&b) == &a)) {
		connections.erase(&b);
	}
}

void Graph::removeConnection(InPort &p)
{
	connections.erase(&p);
}


/**
 * Function iterates through subgraphs starting at the proposed edge of the current block
 * to determine if they reach the starting block.
 * @todo Implement using algorithm from src/core/graphCycles.cpp
 */
bool Graph::formsCycle(OutPort &startPort, InPort &endPort) {

}
