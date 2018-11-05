#pragma once

/**
 * An abstract base class.
 */
class base
{
	public:
	/**
	 * Default constructor.
	 */
	base() = default;

	/**
	 * Default virtual destructor.
	 */
	virtual ~base() = default;

	/**
	 * Default copy constructor.
	 * \param b
	 */
	base(const base& b) = default;

	/**
	 * Default move constructor.
	 * \param b
	 */
	base(base&& b) = default;

	/**
	 * Default copy assignment operator.
	 * \param b
	 * \return
	 */
	base& operator=(const base& b) = default;

	/**
	 * Default move assignment operator.
	 * \param b
	 * \return
	 */
	base& operator=(base&& b) = default;

	/**
	 * Pure virtual member function.
	 */
	virtual void init() = 0;
};
