#include "blockfactory.h"

#include "blocks/vectoraddblock.h"
#include "blocks/vectordotproductblock.h"
#include "blocks/scalaraddblock.h"
#include "blocks/scalarsubblock.h"
#include "blocks/scalarmulblock.h"
#include "blocks/matrixaddblock.h"
#include "blocks/matrixmulblock.h"

BlockBase *BlockFactory::AllocBlock(BlockType t)
{
	BlockBase *b;
	switch (t) {
	case VECTOR_ADD:
		b = new VectorAddBlock(g);
		break;
    case VECTOR_DOTPRODUCT:
        b = new VectorDotProductBlock(g);
        break;
    case SCALAR_ADD:
        b = new ScalarAddBlock(g);
        break;
    case SCALAR_SUB:
        b = new ScalarSubBlock(g);
        break;
    case SCALAR_MUL:
        b = new ScalarMulBlock(g);
        break;
    case MAT_ADD:
        b = new MatrixAddBlock(g);
        break;
    case MAT_MUL:
        b = new MatrixMulBlock(g);
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
