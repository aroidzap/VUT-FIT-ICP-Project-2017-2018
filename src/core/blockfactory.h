#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "blocks.h"
#include <list>

class Graph;
class BlockBase;

class BlockFactory {
private:
	Graph &g;
	std::list<BlockBase*> blocks;
public:
	BlockBase* AllocBlock(BlockType t);
	void FreeBlock(BlockBase*);
	BlockFactory(Graph &g);
	~BlockFactory();
};

#endif // BLOCKFACTORY_H
