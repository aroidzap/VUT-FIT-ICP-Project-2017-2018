#include "graph.h"
#include <utility>

Graph::Graph() : bf(*this), last_computed(nullptr), to_compute(), c_it(to_compute.begin()) { }

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
	computeReset();
}

void Graph::removeBlock(BlockBase *b)
{
	this->blocks.remove(b);
	GetBlockFactory().FreeBlock(b);
	computeReset();
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
	a.eventConnectionChange();
	b.eventConnectionChange();
	computeReset();
	return true;
}

void Graph::removeConnection(OutPort &a, InPort &b)
{
	if ((connections.find(&b) != connections.end()) &&
		(connections.at(&b) == &a)) {
		connections.erase(&b);
		a.eventConnectionChange();
		b.eventConnectionChange();
		computeReset();
	}
}

void Graph::removeConnection(InPort &p)
{
	OutPort *op = getConnectedOutPort(p);
	if (op != nullptr){
		op->eventConnectionChange();
	}
	connections.erase(&p);
	computeReset();
}

bool Graph::allInputsConnected()
{
	for(const auto b : to_compute){
		if(b->Computable() && !b->InputsAreConnected())
		{
			return false;
		}
	}
	return true;
}

void Graph::computeReset() {
	to_compute = blocks;
	c_it = to_compute.begin();
}

bool Graph::computeStep()
{
	last_computed = nullptr;

	if (!allInputsConnected()) {
		return false;
	}

	while (to_compute.size() > 0)
	{
		if ((*c_it)->Computable())
		{
			if ((*c_it)->HasAllValues())
			{
				(*c_it)->Compute();
				last_computed = *c_it;
				to_compute.erase(c_it++);
				break; // block is computed, continue
			} else {
				c_it++;
			}
		}
		else {
			// remove non-computable block
			to_compute.erase(c_it++);
		}
		// cyclic iteration
		if(c_it == to_compute.end()){
			c_it = to_compute.begin();
		}
	}

	// cyclic iteration
	if(c_it == to_compute.end()){
		c_it = to_compute.begin();
	}

	return true;
}

bool Graph::computeAll()
{
	computeReset();
	while(!computeFinished()){
		if(!computeStep()){
			return false;
		}
	}
	return true;
}

bool Graph::computeFinished()
{
	return (to_compute.size() == 0);
}
