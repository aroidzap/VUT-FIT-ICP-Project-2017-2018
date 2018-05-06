/** ICP Project 2017/2018: BlockEditor
 * @file port.h
 * @brief Ports header
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
	 * @param name Name of the port's label
	 */
	Port(const BlockBase & b, const Type &t, std::string name);
	//! Returns port's value
	virtual Type & Value() = 0;
	//! Operator [] overloading for using data type specific strings to access values of the port
	TypeValue & operator[](const std::string &s);

	//! Fires onValueChange callback for this port
	virtual void eventValueChange();
	//! Fires onConnectionChange callback
	void eventConnectionChange();
	//! Sets what to do on connection change
	void onConnectionChange(std::function<void(Port &)> callback);
	//! Sets what to do on value change
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
	 * @param name Name of the port's label
	 */
	InPort(const BlockBase & b, const Type &t, std::string name);
	//! Returns port's value
	Type & Value() override;
};

//! Input port class
class OutPort : public Port
{
public:
	//! Fires onValueChange callback for this port and all connected ports
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
	 * @param name Name of the port's label
	 */
	OutPort(const BlockBase & b, const Type &t, std::string name);
	//! Returns port's value
	Type & Value() override;
};


#endif // PORT_H
