#ifndef PORT_H
#define PORT_H

#include "type.h"

class Port
{
public:
	Port();
	bool HasValue() const = 0;
	const Type & GetValue() const = 0;
};

class InPort : public Port
{
public:
	InPort();
};

class OutPort : public Port
{
public:
	OutPort();
};


#endif // PORT_H
