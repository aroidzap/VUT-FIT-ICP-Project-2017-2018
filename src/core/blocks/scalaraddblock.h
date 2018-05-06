/** ICP Project 2017/2018: BlockEditor
 * @file scalaraddblock.h
 * @brief Scalar addition block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef SCALARADDBLOCK
#define SCALARADDBLOCK

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The scalar addition block class
 *
 * Construction, computation and destruction of a block.
 */
class ScalarAddBlock : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	ScalarAddBlock(Graph &g);
	
	//! Performs the scalar addition
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~ScalarAddBlock() = default;
};

#endif // SCALARADDBLOCK

