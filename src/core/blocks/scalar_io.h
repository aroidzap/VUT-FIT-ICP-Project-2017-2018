/** ICP Project 2017/2018: BlockEditor
 * @file scalar_io.h
 * @brief Scalar IO block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef SCALAR_IO_H
#define SCALAR_IO_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The scalar input block class
 *
 * Construction, computation and destruction of a block.
 */
class ScalarInput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	ScalarInput(Graph &g);
	//! Propagates values from text fields to an out port
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~ScalarInput() = default;
};

/**
 * @brief The scalar output block class
 *
 * Construction, computation and destruction of a block.
 */
class ScalarOutput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	ScalarOutput(Graph &g);
	//! Shows values from in ports
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~ScalarOutput() = default;
};

#endif // SCALAR_IO_H
