/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: types.h
*/

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
	mat2(double m11, double m12, double m21, double m22);
};

#endif // TYPES_H
