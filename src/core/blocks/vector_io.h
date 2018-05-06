/** ICP Project 2017/2018: BlockEditor
 * @file vector_io.h
 * @brief Vector IO block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef VECTORINPUT_H
#define VECTORINPUT_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The vector input block class
 *
 * Construction, computation and destruction of a block.
 */
class VectorInput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	VectorInput(Graph &g);
	//! Not used for Input Blocks
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~VectorInput() = default;
};

/**
 * @brief The vector output block class
 *
 * Construction, computation and destruction of a block.
 */
class VectorOutput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	VectorOutput(Graph &g);
	//! Not used for Output Blocks
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~VectorOutput() = default;
};

#endif // VECTORADDBLOCK_H
