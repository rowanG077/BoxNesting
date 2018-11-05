#include <box_nesting/Box.hpp>

#include <algorithm>

namespace BoxNesting
{

Box::Box(double x, double y, double z) : sideLengths({x, y, z})
{
    std::sort(this->sideLengths.begin(), this->sideLengths.end());
}

bool Box::isNestable(const Box& b) const
{
	for (std::size_t i = 0; i < this->sideLengths.size(); ++i) {
		if (this->sideLengths.at(i) >= b.sideLengths.at(i)) {
			return false;
		}
	}

	return true;
}
}