if(NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/.git")
	return()
endif()

find_package(Git REQUIRED)

# output style is:
#	846ffe7, no tag yet
#	846ffe7+, no tag yet, dirty
#	1.3.2, an exact tag
#	1.3.2+, an exact tag, dirty
#	1.3.2-1-g846ffe7, one commit since tag
#	1.3.2-1-g846ffe7+, one commit since tag, dirty
execute_process(COMMAND "${GIT_EXECUTABLE}" describe --dirty=+ --tags --always
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
	OUTPUT_VARIABLE TMP_VER
	OUTPUT_STRIP_TRAILING_WHITESPACE)

# if there is no git tag prefix the CMake version
if(TMP_VER MATCHES "^[0-9a-f]+\\+?$")
	set(TMP_VER "${PROJECT_VERSION}-1-g${TMP_VER}")
endif()

# error if CMakeLists.txt version does not match the latest tag
string(REGEX REPLACE "^(.*)-[0-9]+-g[0-9a-f]+\\+?$" "\\1" TMP_TAG "${TMP_VER}")
# also support dirty tags, e.g. 1.3.2+
if(TMP_VER STREQUAL TMP_TAG)
	string(REGEX REPLACE "^(.*)\\+$" "\\1" TMP_TAG "${TMP_VER}")
endif()
if(NOT PROJECT_VERSION STREQUAL TMP_TAG)
	message(FATAL_ERROR "CMake project version and git tag mismatch! \
CMake: ${PROJECT_VERSION}, Git tag: ${TMP_TAG}.")
endif()

# replace "-1-g" with "-", turning it into e.g. 1.3.2-846ffe7+
string(REGEX REPLACE "^(.*)-[0-9]+-g([0-9a-f]+\\+?)$" "\\1-\\2"
	TMP_VER "${TMP_VER}")

# only set CMAKE variant when local name matches CMAKE name
# this avoids clashing when being used as a subproject
set(PROJECT_VERSION "${TMP_VER}")
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(CMAKE_PROJECT_VERSION "${PROJECT_VERSION}")
endif()

# do not message if actual version did not change
if(NOT PROJECT_VERSION STREQUAL PROJECT_VERSION_PREV)
	set(PROJECT_VERSION_PREV "${PROJECT_VERSION}" CACHE STRING
		"Project version during previous cache build." FORCE)
	mark_as_advanced(PROJECT_VERSION_PREV)
	message(STATUS "Updated version to ${PROJECT_VERSION}.")
endif()

unset(TMP_VER)
unset(TMP_TAG)

# force a reconfigure when the git index changes
# dirty detection won't run every for every build so it may outdated
# when the index/staging area changes it will however trigger
# this balances configuration time and dirty index detection
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
	"${CMAKE_SOURCE_DIR}/.git/index")
