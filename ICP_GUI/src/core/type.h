#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <initializer_list>

class Type
{
private:
	std::map<std::string, double> data;
public:
	Type(std::initializer_list<std::string> components);
	double & operator[](const std::string &s);
	bool type_of(const Type &other);
	friend bool operator== (const Type &a, const Type &b);
};

#endif // TYPE_H
