/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: graph.cpp
*/

#include "graph.h"
#include <utility>
#include <sstream>
#include <iterator>

Graph::Graph() : bf(*this), last_computed(nullptr), to_compute(), c_it(to_compute.begin()) { }

void Graph::SetName(const std::string name)
{
	this->name = name;
}

int Graph::getBlockID(const BlockBase &block) const
{
	int idx = 0;
	for (BlockBase *b : blocks) {
		if (b == &block){
			return idx;
		}
		idx++;
	}
	return -1;
}

void Graph::clearGraph()
{
	for (BlockBase *b : blocks){
		GetBlockFactory().FreeBlock(b);
	}
	blocks.clear();
	connections.clear();
	name.clear();
}

bool Graph::loadGraph(std::stringstream &graph, bool merge)
{
	if(!merge){
		clearGraph();
	}
	// block id offset
	int b_id_off = static_cast<int>(blocks.size());

	std::string tmp;
	try {
		// Blocks
		std::getline(graph, tmp,'[');
		if (tmp != "blocks") {
			return false;
		}
		std::getline(graph, tmp, ']');
		std::stringstream block_stream(tmp);
		while(std::getline(block_stream, tmp, ',')){
			BlockType t = static_cast<BlockType>(std::stoi(tmp));
			addBlock(t);
		}

		// Connections
		std::getline(graph, tmp,'[');
		if (tmp != "conn") {
			return false;
		}
		std::getline(graph, tmp, ']');
		std::stringstream conn_stream(tmp);
		while (std::getline(conn_stream, tmp, ',')) {
			std::stringstream conn(tmp);
			std::getline(conn, tmp, '-');
			std::stringstream out(tmp);
			std::getline(conn, tmp, '-');
			std::stringstream in(tmp);
			std::string in_b, in_p, out_b, out_p;
			std::getline(out, out_b, '|');
			std::getline(out, out_p, '|');
			std::getline(in, in_b, '|');
			std::getline(in, in_p, '|');
			auto out_block = this->blocks.begin();
			auto in_block = this->blocks.begin();
			std::advance(out_block, std::stoi(out_b) + b_id_off);
			std::advance(in_block, std::stoi(in_b) + b_id_off);
			OutPort &a = (*out_block)->Output(std::stoi(out_p));
			InPort &b = (*in_block)->Input(std::stoi(in_p));
			addConnection(a, b);
		}
	}
	catch (const std::invalid_argument &e) {
		(e);
		return false;
	}
	return true;
}

std::stringstream Graph::saveGraph()
{
	std::stringstream ss;

	// Blocks
	ss << "blocks[";
	bool first = true;
	for (BlockBase *b : blocks) {
		if(first) {
			first = false;
		} else {
			ss << ",";
		}
		ss << static_cast<int>(b->type);
	}
	ss << "]";

	// Connections
	ss << "conn[";
	first = true;
	for (std::pair<InPort *, OutPort *> p : connections) {
		if(first) {
			first = false;
		} else {
			ss << ",";
		}
		ss << p.second->block.getID() << "|";
		ss << p.second->getID() << "-";
		ss << p.first->block.getID() << "|";
		ss << p.first->getID();
	}
	ss << "]";

	return std::move(ss);
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
	for(int i = 0; i < b->InputCount(); i++){
		removeConnection(b->Input(i));
	}
	for(int i = 0; i < b->OutputCount(); i++){
		removeConnection(b->Output(i));
	}
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

void Graph::removeConnection(InPort &p)
{
	OutPort *op = getConnectedOutPort(p);
	if (op != nullptr){
		op->eventConnectionChange();
	}
	connections.erase(&p);
	computeReset();
}

void Graph::removeConnection(OutPort &p)
{
	for(auto it = connections.begin(); it != connections.end();){
		if ((*it).second == &p) {
			(*it).first->eventConnectionChange();
			(*it).second->eventConnectionChange();
			it = connections.erase(it);
		} else {
			it++;
		}
	}
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
