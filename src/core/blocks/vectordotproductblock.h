/** ICP Project 2017/2018: BlockEditor
 * @file vectordotproductblock.h
 * @brief Vector dot product block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef VECTORDOTPRODBLOCK_H
#define VECTORDOTPRODBLOCK_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The vector dot product block class
 *
 * Construction, computation and destruction of a block.
 */
class VectorDotProductBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	VectorDotProductBlock(Graph &g);
	
	//! Computes the vectors' dot product
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~VectorDotProductBlock() = default;
};

#endif // VECTORDOTPRODBLOCK_H
