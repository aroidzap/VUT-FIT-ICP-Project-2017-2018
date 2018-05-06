/** ICP Project 2017/2018: BlockEditor
 * @file matrixaddblock.h
 * @brief Matrix addition block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef MATRIXADDBLOCK
#define MATRIXADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The matrix addition block class
 *
 * Construction, computation and destruction of a block.
 */
class MatrixAddBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	MatrixAddBlock(Graph &g);
	
	//! Performs the matrix addition
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~MatrixAddBlock() = default;
};

#endif // MATRIXADDBLOCK

