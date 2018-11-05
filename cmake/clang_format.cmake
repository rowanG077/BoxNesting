if(NOT CLANG_FORMAT_FOUND)
	find_program(CLANG_FORMAT_PATH
		NAMES clang-format
		DOC "Path to clang-format.")

	if(NOT CLANG_FORMAT_PATH)
		message(FATAL_ERROR "Could not find clang-format.")
	endif()
	set(CLANG_FORMAT_FOUND ON CACHE BOOL "Found clang-format.")
	mark_as_advanced(CLANG_FORMAT_FOUND)
	message(STATUS "Found clang-format: ${CLANG_FORMAT_PATH}")
endif()

add_custom_target(format
	COMMENT "Formatting source code"
	COMMAND ./clang_format.sh -c "${CLANG_FORMAT_PATH}" format
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")

add_custom_target(format_check
	COMMENT "Running format check"
	COMMAND WERROR=${WERROR} ./clang_format.sh -c "${CLANG_FORMAT_PATH}" check
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
