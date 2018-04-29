#include "type.h"
#include <utility>
#include <sstream>

Type::Type(std::initializer_list<std::string> components) : null_data(true)
{
	for (const auto &component : components) {
		this->data.insert(std::pair<std::string, TypeValue>(component, TypeValue(*this, 0.0)));
	}
}

// access component of type
TypeValue &Type::operator[](const std::string &component)
{
	return this->data.at(component);
}

bool Type::isNull() const
{
	return null_data;
}

void Type::setNull()
{
	null_data = true;
}

// check type compatibility
bool Type::type_of(const Type &other)
{
	for (const auto &element : this->data) {
		if (other.data.count(element.first) == 0) {
			return false;
		}
	}
	return true;
}

Type::operator std::string()
{
	std::stringstream ss;
	for(const auto &elem : data)
	{
		ss << elem.first << ": ";
		if (isNull()) {
			ss << "Null";
		} else {
			ss << elem.second;
		}
		ss << "\n";
	}
	return ss.str();
}

// 'a' values equals 'b' values
bool operator==(const Type &a, const Type &b)
{
	for (const auto &element : a.data) {
		if (b.data.at(element.first) != element.second) {
			return false;
		}
	}
	return true;
}

TypeValue::TypeValue(Type &type) : type(type), data(0.0)
{
	this->type = type;
}

TypeValue::TypeValue(Type &type, double value) : TypeValue(type)
{
	this->operator=(value);
}

TypeValue::operator const double &() const
{
	return this->data;
}

TypeValue &TypeValue::operator=(const double &value)
{
	this->data = value;
	this->type.null_data = false;
	return *this;
}

bool operator==(const TypeValue &a, const TypeValue &b)
{
	return a.data == b.data;
}
