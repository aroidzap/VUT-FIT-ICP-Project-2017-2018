#include "blockfactory_ui.h"
#include "port_ui.h"
#include "graph_ui.h"
#include "block_ui.h"

#include "../core/blocks/scalar_io.h"
#include "../core/blocks/vector_io.h"
#include "../core/blocks/matrix_io.h"
#include "../core/blocks/vectoraddblock.h"
#include "../core/blocks/vectordotproductblock.h"
#include "../core/blocks/scalaraddblock.h"
#include "../core/blocks/scalarsubblock.h"
#include "../core/blocks/scalarmulblock.h"
#include "../core/blocks/matrixaddblock.h"
#include "../core/blocks/matrixmulblock.h"

BlockBase *BlockFactoryUI::AllocBlock(BlockType t)
{
	GraphUI *gp = static_cast<GraphUI*>(&g);
	BlockBase *b;
	switch (t) {
	case SCAL_INPUT:
		b = new InputBlockUI<ScalarInput>(BlockUI<ScalarInput>(ScalarInput(g), gp), gp);
		break;
	case SCAL_OUTPUT:
		b = new OutputBlockUI<ScalarOutput>(BlockUI<ScalarOutput>(ScalarOutput(g), gp), gp);
		break;
	case VECTOR_INPUT:
		b = new InputBlockUI<VectorInput>(BlockUI<VectorInput>(VectorInput(g), gp), gp);
		break;
	case VECTOR_OUTPUT:
		b = new OutputBlockUI<VectorOutput>(BlockUI<VectorOutput>(VectorOutput(g), gp), gp);
		break;
	case MAT2_INPUT:
		b = new InputBlockUI<MatrixInput>(BlockUI<MatrixInput>(MatrixInput(g), gp), gp);
		break;
	case MAT2_OUTPUT:
		b = new OutputBlockUI<MatrixOutput>(BlockUI<MatrixOutput>(MatrixOutput(g), gp), gp);
		break;
	case VECTOR_ADD:
		b = new BlockUI<VectorAddBlock>(VectorAddBlock(g), gp);
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
	blocks.push_back(b);
	return b;
}

BlockFactoryUI::BlockFactoryUI(GraphUI &g)
	: BlockFactory(g), block_parent(&g) { }
