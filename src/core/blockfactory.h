/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: blockfactory.h
*/

#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "blocks.h"
#include <list>

class Graph;
class BlockBase;

class BlockFactory {
protected:
	Graph &g;
	std::list<BlockBase*> blocks;
public:
	virtual BlockBase* AllocBlock(BlockType t);
	virtual void FreeBlock(BlockBase *b);
	BlockFactory(Graph &g);
	virtual ~BlockFactory();
};

#endif // BLOCKFACTORY_H
