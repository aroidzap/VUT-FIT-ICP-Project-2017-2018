#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <initializer_list>
#include <iostream>

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
public:
	Type(std::initializer_list<std::string> components);
	Type(const Type &other);
	Type & operator=(const Type &other);
	Type(Type &&other) = delete;
	TypeValue & operator[](const std::string &s);
	bool isNull() const;
	void setNull();
	bool type_of(const Type &other) const; // type comparison
	friend bool operator== (const Type &a, const Type &b); // value comparison
	operator std::string();
};

#endif // TYPE_H
