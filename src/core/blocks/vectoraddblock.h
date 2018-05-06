/** ICP Project 2017/2018: BlockEditor
 * @file vectoraddblock.h
 * @brief Vector addition block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef VECTORADDBLOCK_H
#define VECTORADDBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The vector addition block class
 *
 * Construction, computation and destruction of a block.
 */
class VectorAddBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	VectorAddBlock(Graph &g);
	
	//! Performs the vector addition
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~VectorAddBlock() = default;
};

#endif // VECTORADDBLOCK_H
