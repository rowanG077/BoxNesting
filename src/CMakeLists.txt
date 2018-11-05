# build code as object library for easier linking to tests
add_library(${PROJECT_NAME}_obj OBJECT
	derived.cpp)

add_executable(${PROJECT_NAME}
	main.cpp
	$<TARGET_OBJECTS:${PROJECT_NAME}_obj>)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
