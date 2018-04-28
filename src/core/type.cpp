#include "type.h"
#include <utility>

Type::Type(std::initializer_list<std::string> components)
{
	for (const auto &component : components) {
		this->data.insert(std::pair<std::string, double>(component, 0.0));
	}
}

// access component of type
double &Type::operator[](const std::string &component)
{
	return this->data.at(component);
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
