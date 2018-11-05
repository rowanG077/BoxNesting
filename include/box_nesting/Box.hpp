#pragma once

#include <array>

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
	 * Default virtual destructor.
	 */
	virtual ~Box() = default;

	/**
	 * Default copy constructor.
	 * \param b
	 */
	Box(const Box& b) = default;

	/**
	 * Default move constructor.
	 * \param b
	 */
	Box(Box&& b) = default;

	/**
	 * Default copy assignment operator.
	 * \param b
	 * \return
	 */
	Box& operator=(const Box& b) = default;

	/**
	 * Default move assignment operator.
	 * \param b
	 * \return
	 */
	Box& operator=(Box&& b) = default;

	/**
	 * @brief Construct a new Box object
	 *
	 * @param x The length of the box in the x-direction
	 * @param y The length of the box in the y-direction
	 * @param z The length of the box in the z-direction
	 * @return A new Box object
	 */
	Box(double x, double y, double z);

	/**
	 * @brief Check if this box can nest inside other box
	 *
	 * @param b The box to check if this box can nest inside.
	 * @return True if this box can nest inside the passed box. False otherwise
	 */
	bool isNestable(const Box& b) const;

private:
	/**
	 * @brief The lengths of each side ordered from smallest to longest
	 */
	std::array<double, 3> sideLengths;
};
}
