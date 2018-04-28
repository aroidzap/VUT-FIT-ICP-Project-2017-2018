#ifndef PORT_H
#define PORT_H

#include "type.h"

class Port
{
public:
	Port();
	virtual bool HasValue() const = 0;
	virtual const Type & GetValue() const = 0;
};

class InPort : public Port
{
public:
	InPort();
	bool HasValue() const override;
	const Type & GetValue() const override;
};

class OutPort : public Port
{
public:
	OutPort();
	bool HasValue() const override;
	const Type & GetValue() const override;
};


#endif // PORT_H
