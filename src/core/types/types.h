/** ICP Project 2017/2018: BlockEditor
 * @file types.h
 * @brief Custom data types for schemes header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef TYPES_H
#define TYPES_H

#include "../type.h"

/**
 * @brief Scalar value
 */
class scal : public Type {
public:
	scal();
	scal(double val);
};

/**
 * @brief 2D vector
 */
class vec2 : public Type {
public:
	vec2();
	vec2(double x, double y);
};

/**
 * @brief 2x2 matrix
 */
class mat2 : public Type {
public:
	mat2();
	mat2(double m11, double m12, double m21, double m22);
};

#endif // TYPES_H
