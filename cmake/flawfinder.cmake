if(NOT FLAWFINDER_FOUND)
	find_program(FLAWFINDER_PATH
		NAMES flawfinder
		DOC "Path to flawfinder.")

	if(NOT FLAWFINDER_PATH)
		message(FATAL_ERROR "Could not find flawfinder.")
	endif()
	set(FLAWFINDER_FOUND ON CACHE BOOL "Found flawfinder.")
	mark_as_advanced(FLAWFINDER_FOUND)
	message(STATUS "Found flawfinder: ${FLAWFINDER_PATH}")
endif()

if(${WERROR})
	set(OPT "--error-level=1")
else()
	unset(OPT)
endif()

add_custom_target(flawfinder
	COMMENT "Running flawfinder"
	COMMAND "${FLAWFINDER_PATH}" -m 1 -C -c -D -Q ${OPT} -- .
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
