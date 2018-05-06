/** ICP Project 2017/2018: BlockEditor
 * @file matrix_io.h
 * @brief Matrix IO block header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include "../blockbase.h"
#include "../graph.h"

/**
 * @brief The matrix input block class
 *
 * Construction, computation and destruction of a block.
 */
class MatrixInput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	MatrixInput(Graph &g);
	//! Propagates values from text fields to an out port
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~MatrixInput() = default;
};

/**
 * @brief The matrix output block class
 *
 * Construction, computation and destruction of a block.
 */
class MatrixOutput : public BlockBase
{
public:
	//! Constructor

	//! @param g Graph object - parent scheme
	MatrixOutput(Graph &g);
	//! Shows values from in ports
	void Compute() override;
	//! Virtual destructor to prevent leaks
	virtual ~MatrixOutput() = default;
};


#endif // MATRIX_IO_H
