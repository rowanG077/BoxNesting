#include <box_nesting/Box.hpp>

#include <algorithm>

namespace BoxNesting
{
Box::Box(const std::array<double, 3>& sideLengths) : sideLengths(sideLengths)
{
	std::sort(this->sideLengths.begin(), this->sideLengths.end());

	for (auto l : this->sideLengths) {
		if (l <= Box::minLength || l >= Box::maxLength) {
			throw std::invalid_argument("Dimensions of box are not within 0.5m to 1m range.");
		}
	}
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
} // BoxNesting