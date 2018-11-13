set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set warning flags for debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
		CMAKE_C_COMPILER_ID STREQUAL "GNU")
		add_compile_options(-Wall -Wextra -Wconversion)
		if(${WERROR})
			add_compile_options(-Werror)
		endif()
	else()
		message(WARNING "Warnings not supported for current compiler.")
	endif()
endif()

# set optimization flags for release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
		CMAKE_C_COMPILER_ID STREQUAL "GNU")
		add_compile_options(-O3)
		if(${WERROR})
			add_compile_options(-Werror)
		endif()
	else()
		message(WARNING "Optimization not supported for current compiler.")
	endif()
endif()

if(${COVERAGE})
	include(coverage)
endif()

if(${CLANG_TIDY})
	include(clang_tidy)
endif()

if(${SANITISE})
	include(sanitise)
endif()

add_subdirectory(src)

if(${TEST})
	enable_testing()
	include(catch)
	add_subdirectory(test)
endif()
