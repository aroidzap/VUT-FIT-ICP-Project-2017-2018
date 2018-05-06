/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: type.h
*/

#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <initializer_list>
#include <iostream>
#include <functional>

class Type;

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

class Type
{
	friend class TypeValue;
private:
	bool null_data;
	std::map<std::string, TypeValue> data;
	std::function<void(void)> valueChanged;
public:
	void onValueChange(std::function<void(void)> callback);
	Type(std::initializer_list<std::string> components);
	Type(const Type &other);
	Type & operator=(const Type &other);
	Type(Type &&other) = delete;
	TypeValue & operator[](const std::string &s);
	const std::map<std::string, TypeValue> Data();
	bool isNull() const;
	void setNull();
	bool type_of(const Type &other) const; // type comparison
	friend bool operator== (const Type &a, const Type &b); // value comparison
	operator std::string();
};

#endif // TYPE_H
