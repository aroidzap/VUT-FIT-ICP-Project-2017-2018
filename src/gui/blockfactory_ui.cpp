#include "blockfactory_ui.h"
#include "port_ui.h"
#include "graph_ui.h"
#include "block_ui.h"

#include "../core/blocks/vectoraddblock.h"

BlockBase *BlockFactoryUI::AllocBlock(BlockType t)
{
	BlockBase *b;
	switch (t) {
	case VECTOR_ADD:
		b = new BlockUI<VectorAddBlock>(VectorAddBlock(g), static_cast<GraphUI*>(&g));
		break;
	default:
		return nullptr;
	}
	// TODO: promote Ports to PortUI
	blocks.push_back(b);
	return b;
}

BlockFactoryUI::BlockFactoryUI(GraphUI &g)
	: BlockFactory(g), block_parent(&g) { }
