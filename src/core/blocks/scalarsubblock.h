/** ICP Project 2017/2018: BlockEditor
 * @file scalarsubblock.h
 * @brief Scalar subtraction block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef SCALARSUBBLOCK_H
#define SCALARSUBBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The scalar subtraction block class
 *
 * Construction, computation and destruction of a block.
 */
class ScalarSubBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	ScalarSubBlock(Graph &g);
	
	//! Performs the scalar subtraction
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~ScalarSubBlock() = default;
};

#endif // SCALARSUBBLOCK_H

