/** ICP Project 2017/2018: BlockEditor
 * @file graph.cpp
 * @brief Core graph functionality
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "graph.h"
#include <utility>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <algorithm>

Graph::Graph() : bf(*this), to_compute(), c_it(to_compute.begin()), last_computed(nullptr) { }

std::string Graph::GetName() const
{
	return this->name;
}

void Graph::SetName(const std::string name)
{
	this->name = name;
	if (graphChanged) {
		graphChanged();
	}
}

void Graph::onGraphChange(std::function<void ()> callback)
{
	this->graphChanged = callback;
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
	if (graphChanged) {
		graphChanged();
	}
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
		// Graph name
		graph >> std::ws; // skip whitespaces
		std::getline(graph, tmp,'[');
		if (tmp != "graph") {
			return false;
		}
		std::getline(graph, tmp, ']');
		if(merge){
			SetName(GetName() + " + " + tmp);
		} else {
			SetName(tmp);
		}

		// Blocks
		graph >> std::ws; // skip whitespaces
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
		graph >> std::ws; // skip whitespaces
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
	catch (const std::invalid_argument &) {
		return false;
	}
	return true;
}

std::stringstream Graph::saveGraph()
{
	std::stringstream ss;

	// Graph name
	ss << "graph[";
	ss << GetName();
	ss << "]";

	// Blocks
	ss << '\n';
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
	ss << '\n';
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

BlockBase *Graph::addBlock(BlockType t)
{
	BlockBase *b = GetBlockFactory().AllocBlock(t);
	if (b != nullptr) {
		this->blocks.push_back(b);
		computeReset();
		if (graphChanged) {
			graphChanged();
		}
	}
	return b;
}

void Graph::removeBlock(BlockBase *b)
{
	this->blocks.remove(b);
	for(std::size_t i = 0; i < b->InputCount(); i++){
		removeConnection(b->Input(i));
	}
	for(std::size_t i = 0; i < b->OutputCount(); i++){
		removeConnection(b->Output(i));
	}
	GetBlockFactory().FreeBlock(b);
	computeReset();
	if (graphChanged) {
		graphChanged();
	}
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
	if (!a.Value().type_of(b.Value())) {
		return false;
	}
	if (!isAcyclic(a, b)) {
		return false;
	}
	connections.insert(std::pair<InPort *, OutPort *>(&b, &a));
	a.eventConnectionChange();
	b.eventConnectionChange();
	computeReset();
	if (graphChanged) {
		graphChanged();
	}
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
	if (graphChanged) {
		graphChanged();
	}
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
	if (graphChanged) {
		graphChanged();
	}
}

bool Graph::allInputsConnected()
{
	for(const auto b : to_compute){
		if(b->Computable() && !b->InputsAreConnected()) {
			return false;
		}
	}
	return true;
}

void Graph::computeReset()
{
	for (BlockBase *b : blocks){
		if(b->Computable()) { b->Reset(); }
	}
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
/**
 * Directed Acyclic Graph Check
 * Reference: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 */
bool Graph::isAcyclic(OutPort &a, InPort &b)
{
	// std::map<output, inputs> edges
	std::map<const BlockBase*, std::set<const BlockBase*>> dag;

	dag[&(a.block)].insert(&(b.block));
	for(auto &c : connections) {
		dag[&(c.second->block)].insert(&(c.first->block));
	}

	const BlockBase *curr;
	std::list<const BlockBase*> visited;
	std::list<const BlockBase*> stack;

	auto not_visited = [&visited](auto x){
		return std::find(visited.begin(), visited.end(), x) == visited.end();
	};
	auto in_stack = [&stack](auto x){
		return std::find(stack.begin(), stack.end(), x) != stack.end();
	};

	for (auto &c : dag) {
		curr = c.first;
		if (not_visited(curr)) {
			visited.push_back(curr);
			stack.push_back(curr);
		}
		while (stack.size() > 0) {
			curr = stack.back();
			bool move_next = false;
			if (dag.find(curr) != dag.end()) {
				// if current has any connections, loop trough them
				for (auto &next : dag.at(curr)) {
					if(in_stack(next)){
						// graph is not acyclic if next is already in stack
						return false;
					}
					if(not_visited(next)){
						// move to next if not visited
						move_next = true;
						visited.push_back(next);
						stack.push_back(next);
						break;
					}
				}
			}
			if (!move_next){
				stack.pop_back();
			}
		}
	}

	return true;
}
