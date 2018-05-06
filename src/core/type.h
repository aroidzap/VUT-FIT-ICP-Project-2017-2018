/** ICP Project 2017/2018: BlockEditor
 * @file type.h
 * @brief Blocks' data types header file
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <initializer_list>
#include <iostream>
#include <functional>

class Port;
class Type;

//! @brief TypeValue is a single component of Type
class TypeValue {
	friend class Type;
private:
	double data;
	Type &type;
	TypeValue(Type &type, double value = 0.0);
public:
	operator const double &() const;
	TypeValue & operator=(const double &value);
	friend bool operator== (const TypeValue &a, const TypeValue &b);
};

//! @brief Type Class is not polymorphic! Derived classes are used only as predefined Types with assigned name!
class Type
{
	friend class TypeValue;
private:
	bool null_data;
	std::map<std::string, TypeValue> data;
	Port *port;
public:
	Type(std::initializer_list<std::string> components);
	Type(const Type &other);
	Type(const Type &other, Port *port);
	Type & operator=(const Type &other);
	Type(Type &&other) = delete;
	TypeValue & operator[](const std::string &s);
	const std::map<std::string, TypeValue> Data();
	bool isNull() const;
	void setNull();
	//! Type comparison
	bool type_of(const Type &other) const;
	//! Value comparison
	friend bool operator== (const Type &a, const Type &b);
	operator std::string();
};

#endif // TYPE_H
