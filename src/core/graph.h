/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: graph.h
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <initializer_list>
#include <functional>
#include "port.h"
#include "blockbase.h"
#include "blockfactory.h"

class Graph
{
private:
	std::function<void(void)> graphChanged;
	BlockFactory bf;
protected:
	std::string name;
	virtual BlockFactory & GetBlockFactory();
	std::list<BlockBase*> to_compute;
	std::list<BlockBase*>::iterator c_it;
	BlockBase *last_computed;
public:
	std::list<BlockBase*> blocks;
	std::map<InPort *, OutPort *> connections;

	Graph();

	std::string GetName() const;
	void SetName(const std::string name);

	void onGraphChange(std::function<void(void)> callback);

	int getBlockID(const BlockBase &block) const;
	virtual void clearGraph();
	virtual bool loadGraph(std::stringstream &graph, bool merge = false);
	virtual std::stringstream saveGraph();

	void addBlock(BlockType);
	virtual void removeBlock(BlockBase *b);
	OutPort * getConnectedOutPort(InPort &p);
	virtual bool addConnection(OutPort &a, InPort &b);
	virtual void removeConnection(InPort &p);
	virtual void removeConnection(OutPort &p);
	virtual bool allInputsConnected();
	virtual void computeReset();
	virtual bool computeStep();
	virtual bool computeAll();
	bool computeFinished();
	bool isAcyclic(OutPort &a, InPort &b);
	bool isCyclicRec(std::map<const BlockBase*, std::list<const BlockBase*>> &connections, const BlockBase* v, std::map<const BlockBase*,bool> &visited, std::map<const BlockBase*,bool> &recStack);
};

#endif // GRAPH_H
