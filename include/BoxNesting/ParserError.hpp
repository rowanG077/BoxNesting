#pragma once

#include <exception>
#include <stdexcept>
#include <string>

/**
 * @brief Contains code for the boxnesting problem
 */
namespace BoxNesting
{
/**
 * @brief Exception that is thrown when error occurs during parsing
 */
struct ParserError : public std::runtime_error
{
public:
	/**
	 * @brief Construct a new Parser Exception object
	 *
	 * @param msg The message to set
	 * @return A new ParserError object
	 */
	explicit ParserError(const std::string& msg) : std::runtime_error(msg), innerException(nullptr)
	{
	}

	/**
	 * @brief Construct a new Parser Exception object
	 *
	 * @param msg The message to set
	 * @param innerException innerException to set
	 * @return A new ParserError object
	 */
	ParserError(const std::string& msg, const std::exception& innerException) :
		std::runtime_error(msg), innerException(std::make_exception_ptr(innerException))
	{
	}

	/**
	 * @brief Contains the original exception if there was a caught exception
	 */
	const std::exception_ptr innerException;
};
} // BoxNesting