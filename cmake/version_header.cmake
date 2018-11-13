# defines should always use UPPER_CASE naming
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)

# add c++ header which contains project info
configure_file(
	"${PROJECT_SOURCE_DIR}/cmake/version.hpp.in"
	"${PROJECT_SOURCE_DIR}/src/version.hpp")
