#include <box_nesting/derived.hpp>

#include <iostream>

std::string class_types_to_string(class_type t)
{
	switch (t) {
	case class_type::INTERFACE:
		return "INTERFACE";
	case class_type::ABSTRACT:
		return "ABSTRACT";
	case class_type::NORMAL:
		return "NORMAL";
	default:
		return "unknown class type";
	}
}

void derived::init()
{
	std::cout << "hello from ::derived::init()" << std::endl;
}