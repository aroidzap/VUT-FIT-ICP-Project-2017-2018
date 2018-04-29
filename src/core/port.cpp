#include "port.h"

Port::Port(const BlockBase &b, const Type &t, std::string name)
	: block(b), data(t), name(name) { }

TypeValue &Port::operator[](const std::string &s)
{
	return Value()[s];
}

InPort::InPort(const BlockBase &b, const Type &t, std::string name) : Port(b, t, name) { }

bool InPort::HasValue() const
{
	return true; //TODO
}

Type &InPort::Value()
{
	return this->data; //TODO
}
OutPort::OutPort(const BlockBase &b, const Type &t, std::string name) : Port(b, t, name) { }

bool OutPort::HasValue() const
{
	return true; //TODO
}

Type &OutPort::Value()
{
	return this->data; //TODO
}
