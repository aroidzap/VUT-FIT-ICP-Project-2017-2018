#ifndef TYPES_H
#define TYPES_H

#include "../type.h"

class scal : public Type {
public:
	scal();
	scal(double val);
};

class vec2 : public Type {
public:
	vec2();
	vec2(double x, double y);
};

class mat2 : public Type {
public:
	mat2();
};

#endif // TYPES_H
