/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: port.h
*/

#ifndef PORT_H
#define PORT_H

#include <string>
#include "type.h"

class BlockBase;

class Port
{
protected:
	Type data;
	std::function<void(Port &)> connUpdate, valUpdate;
public:
	virtual void eventValueChange();
	void eventConnectionChange();
	void onConnectionChange(std::function<void(Port &)> callback);
	void onValueChange(std::function<void(Port &)> callback);
	const BlockBase &block;
	const std::string name;
	Port(const BlockBase & b, const Type &t, std::string name);
	virtual Type & Value() = 0;
	TypeValue & operator[](const std::string &s);
};

class InPort : public Port
{
public:
	int getID() const;
	InPort(const InPort & other, const BlockBase & b);
	InPort(const BlockBase & b, const Type &t, std::string name);
	Type & Value() override;
};

class OutPort : public Port
{
public:
	void eventValueChange() override;
	int getID() const;
	OutPort(const OutPort & other, const BlockBase & b);
	OutPort(const BlockBase & b, const Type &t, std::string name);
	Type & Value() override;
};


#endif // PORT_H
