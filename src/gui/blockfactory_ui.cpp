#include "blockfactory_ui.h"
#include "port_ui.h"
#include "graph_ui.h"
#include "block_ui.h"

#include "../core/blocks/vector_io.h"
#include "../core/blocks/vectoraddblock.h"

BlockBase *BlockFactoryUI::AllocBlock(BlockType t)
{
	GraphUI *gp = static_cast<GraphUI*>(&g);
	BlockBase *b;
	switch (t) {
	case VECTOR_INPUT:
		b = new InputBlockUI<VectorInput>(BlockUI<VectorInput>(VectorInput(g), gp), gp);
		break;
	case VECTOR_OUTPUT:
		b = new OutputBlockUI<VectorOutput>(BlockUI<VectorOutput>(VectorOutput(g), gp), gp);
		break;
	case VECTOR_ADD:
		b = new BlockUI<VectorAddBlock>(VectorAddBlock(g), gp);
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
