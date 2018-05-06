/** ICP Project 2017/2018: BlockEditor
 * @file port.cpp
 * @brief Ports for blocks
 * and menus created when right-clicking blocks
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "port.h"
#include "blockbase.h"

Port::Port(const Port &other) : data(other.data, this),
	connUpdate(other.connUpdate), valUpdate(other.valUpdate),
	block(other.block), name(other.name) { }

Port::Port(const BlockBase &b, const Type &t, std::string name)
	: data(t, this), block(b), name(name) { }

void Port::eventValueChange() {
	if (valUpdate) {
		valUpdate(*this);
	}
}

void Port::eventConnectionChange() {
	if (connUpdate) {
		connUpdate(*this);
	}
}

void Port::onConnectionChange(std::function<void (Port &)> callback)
{
	this->connUpdate = callback;
}

void Port::onValueChange(std::function<void (Port &)> callback)
{
	this->valUpdate = callback;
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

void OutPort::eventValueChange()
{
	Port::eventValueChange();
	for (auto &c : this->block.graph.connections) {
		if (this == c.second) {
			c.first->eventValueChange();
		}
	}
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
