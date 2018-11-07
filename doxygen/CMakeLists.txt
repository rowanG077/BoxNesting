find_package(Doxygen REQUIRED COMPONENTS dot)

get_target_property(DOXY_DOT_PATH Doxygen::dot IMPORTED_LOCATION)
get_filename_component(DOXY_DOT_PATH "${DOXY_DOT_PATH}" DIRECTORY)
file(TO_NATIVE_PATH "${DOXY_DOT_PATH}" DOXY_DOT_PATH)

set(DOXY_BUILD_HTML "YES")
set(DOXY_BUILD_XML "NO")
set(DOXY_OUTPUT_DIR "${PROJECT_BINARY_DIR}/doxygen")
set(DOXY_FILE "${PROJECT_BINARY_DIR}/doxygen/doxyfile")

configure_file(
	"${PROJECT_SOURCE_DIR}/doxygen/doxyfile.in"
	DOXY_FILE
	@ONLY)

add_custom_target(doxygen
    COMMAND Doxygen::doxygen DOXY_FILE
    COMMENT "Generating HTML API documentation with Doxygen")

add_custom_command(TARGET doxygen POST_BUILD
    COMMAND ;
    COMMENT "Output at ${DOXY_OUTPUT_DIR}/html/index.html")

