#include "types.h"

scal::scal() : Type{"val"} { }

scal::scal(double val) : scal()
{
	operator[]("val") = val;
}

vec2::vec2() : Type{"x", "y"} { }

vec2::vec2(double x, double y) : vec2()
{
	operator[]("x") = x;
	operator[]("y") = y;
}

mat2::mat2() : Type{"m11", "m12", "m21", "m22"} { }

mat2::mat2(double m11, double m12, double m21, double m22) : mat2()
{
	operator[]("m11") = m11;
	operator[]("m12") = m12;
	operator[]("m21") = m21;
	operator[]("m22") = m22;
}
