#include "blockfactory_ui.h"
#include "port_ui.h"

BlockBase *BlockFactoryUI::AllocBlock(BlockType t)
{
	BlockBase *base = BlockFactory::AllocBlock(t);
	BlockUI *b = new BlockUI(*base, block_parent);
	BlockFactory::FreeBlock(base);

	for(auto &p : b->inputs){
		p = InPortUI(p, block_parent);
	}
	for(auto &p : b->outputs){
		p = InPortUI(p, block_parent);
	}

	blocks.push_back(b);
	return b;
}

void BlockFactoryUI::FreeBlock(BlockBase *b)
{
	blocks.remove(b);
	delete b;
}

BlockFactoryUI::BlockFactoryUI(GraphUI &g)
	: BlockFactory(g), block_parent(&g) { }

BlockFactoryUI::~BlockFactoryUI()
{
	for(auto *b : blocks){
		delete b;
	}
}
