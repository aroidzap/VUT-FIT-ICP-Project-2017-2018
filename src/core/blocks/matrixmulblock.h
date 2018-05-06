/** ICP Project 2017/2018: BlockEditor
 * @file matrixmulblock.h
 * @brief Matrix multiplication block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef MATRIXMULBLOCK
#define MATRIXMULBLOCK

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The matrix multiplication block class
 *
 * Construction, computation and destruction of a block.
 */
class MatrixMulBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	MatrixMulBlock(Graph &g);
	
	//! Performs the matrix multiplication
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~MatrixMulBlock() = default;
};

#endif // MATRIXMULBLOCK

