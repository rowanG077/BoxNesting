if(CLANG_TIDY_FOUND)
	return()
endif()

find_program(CLANG_TIDY_PATH
	NAMES clang-tidy
	DOC "Path to clang-tidy.")

if(NOT CLANG_TIDY_PATH)
	message(FATAL_ERROR "Could not find clang-tidy.")
endif()
set(CLANG_TIDY_FOUND ON CACHE BOOL "Found clang-tidy.")
mark_as_advanced(CLANG_TIDY_FOUND)
message(STATUS "Found clang-tidy: ${CLANG_TIDY_PATH}")

set(OPT "${CLANG_TIDY_PATH}")
if(${WERROR})
	set(OPT "${OPT};-warnings-as-errors=*")
endif()

set(CMAKE_C_CLANG_TIDY "${OPT}" CACHE STRING
	"Clang-tidy options for C." FORCE)
set(CMAKE_CXX_CLANG_TIDY "${OPT}" CACHE STRING
	"Clang-tidy options for C++." FORCE)

# hide variables in regular CMake UI
mark_as_advanced(CMAKE_C_CLANG_TIDY CMAKE_CXX_CLANG_TIDY)
