#pragma once

#include "base.hpp"

#include <cstdint>
#include <string>

/**
 * Defines some known class types.
 */
enum class class_type
{
	/**
	 * Has no implementation.
	 */
	INTERFACE,

	/**
	 * Has some implementation.
	 */
	ABSTRACT,

	/**
	 * Has only implementation.
	 */
	NORMAL
};

/**
 * struct containing a min and a max.
 */
struct range
{
	/**
	 * The minimum value.
	 */
	std::uint8_t min;

	/**
	 * The maximum value.
	 */
	std::uint8_t max;
};

/**
 * Convert class_type to a string representation.
 * \param t The type to translate.
 * \return The string variant.
 */
std::string class_types_to_string(class_type t);

/**
 * Class that derives from an abstract base
 */
class derived : public base
{
	public:
	/**
	 * Default constructor.
	 */
	derived() = default;

	~derived() override = default;

	/**
	 * Default copy constructor
	 * \param d
	 */
	derived(const derived& d) = default;

	/**
	 * Default move constructor.
	 * \param d
	 */
	derived(derived&& d) = default;

	/**
	 * Default copy assignment operator.
	 * \param d
	 * \return
	 */
	derived& operator=(const derived& d) = default;

	/**
	 * Default move assignment operator.
	 * \param d
	 * \return
	 */
	derived& operator=(derived&& d) = delete;

	/**
	 * Implemented function
	 */
	void init() override;
};
