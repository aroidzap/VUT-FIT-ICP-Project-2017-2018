/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: port.cpp
*/

#include "port.h"
#include "blockbase.h"

Port::Port(const BlockBase &b, const Type &t, std::string name)
	: data(t), block(b), name(name) { }

void Port::eventConnectionChange() {
	if (connUpdate) {
		connUpdate(*this);
	}
}

void Port::onConnectionChange(std::function<void (Port &)> connUpdate)
{
	this->connUpdate = connUpdate;
}

TypeValue &Port::operator[](const std::string &s)
{
	return Value()[s];
}

int InPort::getID() const
{
	return this->block.getPortID(*this);
}

InPort::InPort(const InPort &other, const BlockBase &b) : InPort(b, other.data, other.name) { }

InPort::InPort(const BlockBase &b, const Type &t, std::string name) : Port(b, t, name) { }

Type &InPort::Value()
{
	const auto &conn = this->block.graph.connections;
	if (conn.find(this) != conn.end()) {
		OutPort *port = this->block.graph.connections.at(this);
		if(port != nullptr){
			return port->Value(); // return value from connected port
		}
	}
	return this->data;
}

int OutPort::getID() const
{
	return this->block.getPortID(*this);
}

OutPort::OutPort(const OutPort &other, const BlockBase &b) : OutPort(b, other.data, other.name) { }

OutPort::OutPort(const BlockBase &b, const Type &t, std::string name) : Port(b, t, name) { }

Type &OutPort::Value()
{
	return this->data;
}
