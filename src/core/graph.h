/**
 * @file graph.h
 * @brief Graph class header
 * @author Tomáš Pazdiora
 * @author Michal Pospíšil
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include "xml.h"
#include "port.h"
#include "blockbase.h"
#include "blockfactory.h"

class Graph
{
public: //TODO: private
	BlockFactory bf;
	std::string name;
	std::vector<BlockBase*> blocks;
	std::map<InPort *, OutPort *> connections;
public:
	Graph(const XML & xml);
	Graph(std::string name);
	Graph(std::string name, std::initializer_list<BlockType> blocks);
	const XML & saveGraph();

	void addBlock(BlockType);
	void removeBlock(BlockBase *b);
	void addConnection(OutPort &a, InPort &b);
	void removeConnection(OutPort &a, InPort &b);
	void removeConnection(InPort &p);
	void computeReset();
	void computeStep();
	void computeAll();

    /**
     * @brief Checks if proposed connection creates a cycle
     * @param startPort Port where the connection starts
     * @param endPort Port where the connection should end
     * @return True when cycle is detected after adding the proposed connection, else false
     */
    bool formsCycle(OutPort &startPort, InPort &endPort);
};

#endif // GRAPH_H
