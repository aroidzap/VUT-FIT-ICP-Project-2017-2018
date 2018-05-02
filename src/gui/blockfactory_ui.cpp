#include "blockfactory_ui.h"
#include "port_ui.h"
#include "graph_ui.h"
#include "block_ui.h"

#include "../core/blocks/vectoraddblock.h"
#include "../core/blocks/vectordotproductblock.h"
#include "../core/blocks/scalaraddblock.h"
#include "../core/blocks/scalarsubblock.h"
#include "../core/blocks/scalarmulblock.h"
#include "../core/blocks/matrixaddblock.h"
#include "../core/blocks/matrixmulblock.h"

BlockBase *BlockFactoryUI::AllocBlock(BlockType t)
{
	BlockBase *b;
	switch (t) {
	case VECTOR_ADD:
		b = new BlockUI<VectorAddBlock>(VectorAddBlock(g), static_cast<GraphUI*>(&g));
		break;
    case VECTOR_DOTPRODUCT:
        b = new BlockUI<VectorDotProductBlock>(VectorDotProductBlock(g), static_cast<GraphUI*>(&g));
        break;
    case SCALAR_ADD:
        b = new BlockUI<ScalarAddBlock>(ScalarAddBlock(g), static_cast<GraphUI*>(&g));
        break;
    case SCALAR_SUB:
        b = new BlockUI<ScalarSubBlock>(ScalarSubBlock(g), static_cast<GraphUI*>(&g));
        break;
    case SCALAR_MUL:
        b = new BlockUI<ScalarMulBlock>(ScalarMulBlock(g), static_cast<GraphUI*>(&g));
        break;
    case MAT_ADD:
        b = new BlockUI<MatrixAddBlock>(MatrixAddBlock(g), static_cast<GraphUI*>(&g));
        break;
    case MAT_MUL:
        b = new BlockUI<MatrixMulBlock>(MatrixMulBlock(g), static_cast<GraphUI*>(&g));
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
