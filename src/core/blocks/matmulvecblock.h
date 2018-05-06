/** ICP Project 2017/2018: BlockEditor
 * @file matmulvecblock.h
 * @brief Matrix and vector multiplication block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef MATMULVECBLOCK_H
#define MATMULVECBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The matrix by vector multiplication block class
 *
 * Construction, computation and destruction of a block.
 */
class MatMulVecBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	MatMulVecBlock(Graph &g);
	
	//! Multiplies matrix by a vector
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~MatMulVecBlock() = default;
};

#endif // MATMULVECBLOCK_H
