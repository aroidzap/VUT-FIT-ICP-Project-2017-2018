#include "type.h"
#include <utility>
#include <sstream>
#include <stdexcept>

Type::Type(std::initializer_list<std::string> components) : null_data(true)
{
	for (const auto &component : components) {
		this->data.insert(std::pair<std::string, TypeValue>(component, TypeValue(*this, 0.0)));
	}
}

Type::Type(const Type &other) : null_data(other.null_data) {
	for (const auto &elem : other.data) {
		this->data.insert(std::pair<std::string, TypeValue>(elem.first, TypeValue(*this, elem.second)));
	}
}

Type &Type::operator=(const Type &other)
{
	this->data.clear();
	null_data = other.null_data;
	for (const auto &elem : other.data) {
		this->data.insert(std::pair<std::string, TypeValue>(elem.first, TypeValue(*this, elem.second)));
	}
	return *this;
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
bool Type::type_of(const Type &other) const
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
	if(!a.type_of(b)){
		return false;
	}
	if(a.isNull() || b.isNull()){
		if(a.isNull() && b.isNull()){
			return true;
		} else {
			return false;
		}
	}
	for (const auto &element : a.data) {
		if (b.data.at(element.first) != element.second) {
			return false;
		}
	}
	return true;
}

TypeValue::TypeValue(Type &type) : type(type), data(0.0) { }

TypeValue::TypeValue(Type &type, double value) : TypeValue(type)
{
	this->operator=(value);
}

TypeValue::operator const double &() const
{
	if(this->type.isNull()){
		throw std::runtime_error("Trying to access null TypeValue!");
	}
	return this->data;
}

// after setting any component to some value, other components are not null anymore and are set to default value '0.0'
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
