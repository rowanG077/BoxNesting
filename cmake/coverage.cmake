if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(FATAL_ERROR
		"Code coverage is only supported for CMAKE_BUILD_TYPE=DEBUG.")
endif()

if(CMAKE_CXX_COMPILER_ID AND
		(NOT CMAKE_C_COMPILER_ID STREQUAL CMAKE_CXX_COMPILER_ID))
	message(FATAL_ERROR "C, C++ compilers cannot differ for COVERAGE=ON.")
endif()

if(${SANITISE})
	message(FATAL_ERROR "COVERAGE and SANITISE are mutually exclusive.")
endif()

# find coverage tools, gcov is for GCC and llvm-cov for clang
# llvm-cov has to wrapped with the gcov option
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
	if(NOT LLVMCOV_FOUND)
		find_program(LLVMCOV_PATH
			NAMES llvm-cov
			DOC "Path to llvm-cov.")

		if(NOT LLVMCOV_PATH)
			message(FATAL_ERROR "Could not find llvm-cov.")
		endif()
		set(LLVMCOV_FOUND ON CACHE BOOL "Found llvm-cov.")
		mark_as_advanced(LLVMCOV_FOUND)
		message(STATUS "Found llvm-cov: ${LLVMCOV_PATH}")

		set(GCOV_PATH "${PROJECT_BINARY_DIR}/llvm-cov.sh")

		# wrap llvm-cov to have behaviour like gcov
		file(WRITE "${GCOV_PATH}"
			"#!/bin/sh\nexec \"${LLVMCOV_PATH}\" gcov \"$@\"")

		execute_process(COMMAND chmod +x "${GCOV_PATH}")
	endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	if(NOT GCOV_FOUND)
		find_program(GCOV_PATH
			NAMES gcov
			DOC "Path to gcov.")
		if(NOT GCOV_PATH)
			message(FATAL_ERROR "Could not find gcov.")
		endif()
		set(GCOV_FOUND ON CACHE BOOL "Found gcov.")
		mark_as_advanced(GCOV_FOUND)
		message(STATUS "Found gcov: ${GCOV_PATH}")
	endif()
else()
	message(FATAL_ERROR
		"Code coverage not supported for current compiler.")
endif()

if(NOT LCOV_FOUND)
	find_program(LCOV_PATH
		NAMES lcov
		DOC "Path to lcov.")
	if(NOT LCOV_PATH)
		message(FATAL_ERROR "Could not find lcov.")
	endif()
	set(LCOV_FOUND ON CACHE BOOL "Found lcov.")
	mark_as_advanced(LCOV_FOUND)
	message(STATUS "Found lcov: ${LCOV_PATH}")
endif()

if(NOT GENHTML_FOUND)
	find_program(GENHTML_PATH
		NAMES genhtml
		DOC "Path to genhtml.")
	if(NOT GENHTML_PATH)
		message(FATAL_ERROR "Could not find genhtml.")
	endif()
	set(GENHTML_FOUND ON CACHE BOOL "Found genhtml.")
	mark_as_advanced(GENHTML_FOUND)
	message(STATUS "Found genhtml: ${GENHTML_PATH}")
endif()

# add necessary compile and linker flags
add_compile_options(--coverage)
if(NOT CMAKE_EXE_LINKER_FLAGS MATCHES "(^| +)--coverage($| +)")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage"
		CACHE STRING "Linker flags used to create executables."
		FORCE)
endif()
if(NOT CMAKE_MODULE_LINKER_FLAGS MATCHES "(^| +)--coverage($| +)")
	set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --coverage"
		CACHE STRING "Linker flags used to create modules."
		FORCE)
endif()
if(NOT CMAKE_SHARED_LINKER_FLAGS MATCHES "(^| +)--coverage($| +)")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage"
		CACHE STRING "Linker flags used to create shared libraries."
		FORCE)
endif()
if(NOT CMAKE_STATIC_LINKER_FLAGS MATCHES "(^| +)--coverage($| +)")
	set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} --coverage"
		CACHE STRING "Linker flags used to create static libraries."
		FORCE)
endif()

# resets coverage counters
add_custom_target(coverage_reset
	COMMAND "${LCOV_PATH}" --zerocounters --directory .
	COMMENT "Resetting coverage counters.")

# add target for generating the actual coverage report
add_custom_target(coverage_report
	# create baselines to make sure untouched files show up in the report
	COMMAND "${LCOV_PATH}" -q -c -i
		--gcov-tool "\"${GCOV_PATH}\""
		-d . -o coverage_report.base

	# capturing lcov counters and generating report
	COMMAND "${LCOV_PATH}" -q
		--gcov-tool "\"${GCOV_PATH}\""
		--directory . --capture
		--output-file coverage_report.info

	# add baseline counters
	COMMAND "${LCOV_PATH}" -q
		--gcov-tool "\"${GCOV_PATH}\""
		-a coverage_report.base -a coverage_report.info
		--output-file coverage_report.total

	# exclude everything but the project sources
	COMMAND "${LCOV_PATH}" -q
		--gcov-tool "\"${GCOV_PATH}\""
		-e coverage_report.total "\"${PROJECT_SOURCE_DIR}/*\""
		--output-file coverage_report.info.cleaned

	# generate html report and remove intermediate reports.
	COMMAND "${GENHTML_PATH}"
		-o coverage_report coverage_report.info.cleaned
	COMMAND "${CMAKE_COMMAND}" -E remove coverage_report.base
		coverage_report.info coverage_report.all coverage_report.total
		coverage_report.info.cleaned

	WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
	COMMENT "Generating html report from coverage data.")

# show info where to find the report
add_custom_command(TARGET coverage_report POST_BUILD
	COMMAND ;
	COMMENT "Report is available at ${PROJECT_BINARY_DIR}\
/coverage_report/index.html.")
