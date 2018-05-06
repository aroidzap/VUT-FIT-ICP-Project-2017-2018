/** ICP Project 2017/2018: BlockEditor
 * @file scalarmulblock.h
 * @brief Scalar multiplication block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef SCALARMULBLOCK_H
#define SCALARMULBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The scalar multiplication block class
 *
 * Construction, computation and destruction of a block.
 */
class ScalarMulBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	ScalarMulBlock(Graph &g);
	
	//! Performs the scalar multiplication
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~ScalarMulBlock() = default;
};

#endif // SCALARMULBLOCK_H

