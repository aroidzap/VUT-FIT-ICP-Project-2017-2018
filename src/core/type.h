#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <initializer_list>

class Type;

class TypeValue {
private:
	double data;
	Type &type;
public:
	TypeValue(Type &type);
	TypeValue(Type &type, double value);
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
	TypeValue & operator[](const std::string &s);
	bool isNull() const;
	bool type_of(const Type &other);
	friend bool operator== (const Type &a, const Type &b);
};

#endif // TYPE_H
