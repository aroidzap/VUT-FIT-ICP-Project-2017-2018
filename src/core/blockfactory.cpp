#include "blockfactory.h"

#include "blocks/vectoraddblock.h"

BlockBase *BlockFactory::AllocBlock(BlockType t)
{
	BlockBase *b;
	switch (t) {
	case VECTOR_ADD:
		b = new VectorAddBlock(g);
		break;
	default:
		return nullptr;
	}
	blocks.push_back(b);
	return b;
}

void BlockFactory::FreeBlock(BlockBase *b)
{
	blocks.remove(b);
	delete b;
}

BlockFactory::BlockFactory(Graph &g) : g(g) { }

BlockFactory::~BlockFactory()
{
	for(BlockBase *b : blocks){
		delete b;
	}
}
