#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "blocks.h"
#include <list>

class Graph;
class BlockBase;

class BlockFactory {
private:
	std::list<BlockBase*> blocks;
protected:
	Graph &g;
public:
	virtual BlockBase* AllocBlock(BlockType t);
	virtual void FreeBlock(BlockBase *b);
	BlockFactory(Graph &g);
	virtual ~BlockFactory();
};

#endif // BLOCKFACTORY_H
