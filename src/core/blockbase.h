/** ICP Project 2017/2018: BlockEditor
 * @file blockbase.h
 * @brief Base class for blocks header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <string>
#include <vector>
#include <initializer_list>
#include "port.h"
#include "graph.h"
#include "blocks.h"

class Graph;

/**
 * @brief Base block definition.
 * Every block inherits basic functions from this class
 * and implements its computation method over it.
 */
class BlockBase {
private:
	/**
	 * @brief Vector of input ports
	 */
	std::vector<InPort> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	/**
	 * @brief Vector of output ports
	 */
	std::vector<OutPort> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
protected:
	BlockBase(Graph &g, BlockType type, std::string name);
	BlockBase(Graph &g, BlockType type, std::string name,
			  std::initializer_list<InPort> inputs,
			  std::initializer_list<OutPort> outputs);
public:
	/**
	 * @brief A reference to the parent Graph object.
	 */
	Graph &graph;
	/**
	 * @brief Type of the block.
	 * See BlockType.
	 */
	const BlockType type;
	/**
	 * @brief Human readable name of a block type
	 */
	const std::string name;
	/**
	 * @brief Gets unique ID of a block
	 * @return ID of a block
	 */
	int getID() const;
	/**
	 * @brief Gets unique ID of a port
	 * @param port Input port
	 * @return ID of a port
	 */
	virtual int getPortID(const InPort &port) const;
	/**
	 * @brief Gets unique ID of a port
	 * @param port Output port
	 * @return ID of a port
	 */
	virtual int getPortID(const OutPort &port) const;
	/**
	 * @brief Gets address of a port
	 * @param port ID of an input port
	 * @return Address of an input port
	 */
	virtual InPort & Input(std::size_t id);
	/**
	 * @brief Returns number of inputs
	 * @return Number of inputs
	 */
	virtual std::size_t InputCount();
	/**
	 * @brief Gets address of a port
	 * @param port ID of an output port
	 * @return Address of an output port
	 */
	virtual OutPort & Output(std::size_t id);
	/**
	 * @brief Returns number of outputs
	 * @return Number of inputs
	 */
	virtual std::size_t OutputCount();

	/**
	 * @brief Checks if all inputs are non-null values
	 * @return True when all inputs are non-null, false otherwise
	 */
	bool HasAllValues();
	/**
	 * @brief Checks that all inputs are connected with some blocks
	 * @return True when all inputs are connected, false otherwise
	 */
	bool InputsAreConnected();
	virtual bool Computable();
	/**
	 * @brief Sets all output port's values to Null
	 */
	void Reset();
	/**
	 * @brief Virtual method that is implemented by every block type
	 */
	virtual void Compute() = 0;

	//! Virtual destructor to prevent leaks
	virtual ~BlockBase() = default;
};

#endif // BLOCKBASE_H
