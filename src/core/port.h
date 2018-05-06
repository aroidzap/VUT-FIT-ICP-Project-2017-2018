/** ICP Project 2017/2018: BlockEditor
 * @file port.h
 * @brief Block port header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef PORT_H
#define PORT_H

#include <string>
#include "type.h"

class BlockBase;

//! Class defining plain port
class Port
{
protected:
	//! Data type
	Type data;
	std::function<void(Port &)> connUpdate, valUpdate;
public:
	//! Parent block reference
	const BlockBase &block;
	//! Human readable block name
	const std::string name;

	//! Copy constructor
	Port(const Port &other);
	/**
	 * @brief Constructor
	 * @param b Block where to create the new port
	 * @param t Type of the port
	 * @param name Name of the port's data type
	 */
	Port(const BlockBase & b, const Type &t, std::string name);
	//! Value of the block
	virtual Type & Value() = 0;
	//! Operator [] overloading for using data type specific strings to access values of the block
	TypeValue & operator[](const std::string &s);

	//! Updates value of the block when the underlying data are changed
	virtual void eventValueChange();
	//! Updates the connection when they are changed
	void eventConnectionChange();
	//! Calls block's compute function when connections change
	void onConnectionChange(std::function<void(Port &)> callback);
	//! Calls block's compute functions when values change
	void onValueChange(std::function<void(Port &)> callback);
};

//! Input port class
class InPort : public Port
{
public:
	//! Get input port ID
	//! @return ID of the port
	int getID() const;
	//! Input port copy constructor
	InPort(const InPort & other, const BlockBase & b);
	/**
	 * @brief Input port constructor
	 * @param b Block where the port is created
	 * @param t Type of the port
	 * @param name Name of the data type
	 */
	InPort(const BlockBase & b, const Type &t, std::string name);
	//! Returns data type of block's value
	Type & Value() override;
};

//! Input port class
class OutPort : public Port
{
public:
	//! Update block's value when other values change
	void eventValueChange() override;
	//! Get output port ID
	//! @return ID of the port
	int getID() const;
	//! Input port copy constructor
	OutPort(const OutPort & other, const BlockBase & b);
	/**
	 * @brief Input port constructor
	 * @param b Block where the port is created
	 * @param t Type of the port
	 * @param name Name of the data type
	 */
	OutPort(const BlockBase & b, const Type &t, std::string name);
	//! Returns data type of block's value
	Type & Value() override;
};


#endif // PORT_H
