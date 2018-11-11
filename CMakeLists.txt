# 3.8.2 required for CMAKE_CXX_STANDARD 17
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# set build type to release if none is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# options
option(CLANG_TIDY "Check code with clang-tidy." OFF)
option(CODE "Build primary libraries and executables." ON)
option(COVERAGE "Instrument code with coverage flags." OFF)
option(DOXYGEN "Add \"doxygen\" target which builds doxygen HTML output from the sources." OFF)
option(FORMAT "Add \"format\" target which runs clang-format." OFF)
option(FLAWFINDER "Add \"flawfinder\" target which checks code." OFF)
option(SANITISE "Add -fsanitize=address and -fsanitize=undefined flags." OFF)
option(TEST "Build unit and functional tests." OFF)
option(WERROR "Make all warnings into errors." OFF)

# disable base languages
unset(PROJECT_LANGUAGES)

if(${CODE})
	set(PROJECT_LANGUAGES ${PROJECT_LANGUAGES} C CXX)
endif()

project(BoxNesting
	VERSION 1.0.0
	DESCRIPTION "Algorithms and Datastructures practicum 1 box nesting algorithm"
	LANGUAGES ${PROJECT_LANGUAGES})
set(PROJECT_VERSION_SUFFIX "") # alpha/beta/rc, e.g. "-rc0"
set(PROJECT_VERSION "${PROJECT_VERSION}${PROJECT_VERSION_SUFFIX}")
set(PROJECT_AUTHOR "Ties Klappe & Rowan Goemans")
set(PROJECT_COPYRIGHT "Copyright (C) 2018 Ties Klappe & Rowan Goemans")
set(PROJECT_MAIL "R.Goemans@student.science.ru.nl")
# only set CMAKE variant when local name matches CMAKE name
# this avoids clashing when being used as a subproject
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(CMAKE_PROJECT_VERSION "${PROJECT_VERSION}")
	set(CMAKE_PROJECT_VERSION_SUFFIX "${PROJECT_VERSION_SUFFIX}")
	set(CMAKE_PROJECT_AUTHOR "${PROJECT_AUTHOR}")
	set(CMAKE_PROJECT_COPYRIGHT "${PROJECT_COPYRIGHT}")
	set(CMAKE_PROJECT_MAIL "${PROJECT_MAIL}")
endif()
include(version)
include(version_header)

if(${CODE})
	include(code)
elseif(${CLANG_TIDY} OR ${COVERAGE} OR ${SANITISE} OR ${TEST})
	message(FATAL_ERROR "At least one flag enabled that requires CODE=ON.")
endif()

if(${FORMAT})
	include(clang_format)
endif()

if(${FLAWFINDER})
	include(flawfinder)
endif()

if(${FLAWFINDER} OR ${FORMAT})
	include(check)
endif()

if(${DOXYGEN})
	add_subdirectory(doxygen)
endif()