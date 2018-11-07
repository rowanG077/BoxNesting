#pragma once

#include <array>
#include <type_traits>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
/**
 * @brief Class representing a box
 */
class Box
{
public:
	/**
	 * @brief Deleted default constructor
	 */
	Box() = delete;

	/**
	 * Default virtual destructor
	 */
	virtual ~Box() = default;

	/**
	 * Default copy constructor
	 * \param b
	 */
	Box(const Box& b) = default;

	/**
	 * Default move constructor
	 * \param b
	 */
	Box(Box&& b) = default;

	/**
	 * Default copy assignment operator
	 * \param b
	 * \return
	 */
	Box& operator=(const Box& b) = default;

	/**
	 * Default move assignment operator
	 * \param b
	 * \return
	 */
	Box& operator=(Box&& b) = default;

	/**
	 * @brief Construct a new Box object
	 *
	 * @param sideLengths The length of the sides of the box in each dimensions
	 * @return A new Box object
	 */
	explicit Box(const std::array<double, 3>& sideLengths);

	/**
	 * @brief Check if this box can nest inside other box
	 *
	 * @param b The box to check if this box can nest inside
	 * @return True if this box can nest inside the passed box, False otherwise
	 */
	[[nodiscard]] bool isNestable(const Box& b) const;

	/**
	 * @brief Get the side lengths of the box
	 *
	 * @return array containing the side lengths ordered from smallest to largest
	 */
	[[nodiscard]] const std::array<double, 3>& getSideLengths() const { return this->sideLengths; }

	/**
	 * @brief The minimum length that a side of a box may have
	 * 		  Is non-inclusive so the length x > minLength
	 */
	static constexpr double minLength = 0.5;

	/**
	 * @brief The maximum length that a side of a box may have
	 * 		  Is non-inclusive so the length x < maxLength
	 */
	static constexpr double maxLength = 1.0;

	/**
	 * @brief Static assert on the assumption any box can only contain a single box nested inside
	 */
	static_assert(minLength * 2 >= maxLength,
		"More then 1 box can be fit inside a larger box. "
		"The algorithm may only be used in the case that any box can contain a single box.");

private:
	/**
	 * @brief The lengths of each side ordered from smallest to longest
	 */
	std::array<double, 3> sideLengths;
};
}
