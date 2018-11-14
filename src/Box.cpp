#include "Box.hpp"

#include <algorithm>
#include <sstream>

namespace BoxNesting
{
Box::Box(const std::array<float, 3>& sideLengths) : sideLengths(sideLengths)
{
	// Sice we only care whether a box can nest inside another box
	// We can optimize this check by always just sorting the lengths
	// so we don't have to check the permutations of the sidelengths
	std::sort(this->sideLengths.begin(), this->sideLengths.end());

	for (auto l : this->sideLengths) {
		if (l <= Box::minLength || l >= Box::maxLength) {
			std::stringstream ss;
			ss << "Length of a side of a box is not between allowed range: (" << Box::minLength << "," << Box::maxLength
			   << ")";
			throw std::invalid_argument(ss.str());
		}
	}
}

bool Box::operator<(const Box& b) const
{
	const auto sz = this->sideLengths.size();
	for (uint8_t i = 0; i < sz; ++i) {
		if (this->sideLengths[i] >= b.sideLengths[i]) {
			return false;
		}
	}

	return true;
}

const std::array<float, 3>& Box::getSideLengths() const
{
	return this->sideLengths;
}

} // BoxNesting