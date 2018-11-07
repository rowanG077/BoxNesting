include_directories(SYSTEM "${CATCH_INCLUDE_DIR}")

# compile main as object library for usage in tests
add_library(test_obj OBJECT
	main.cpp)

# add all tests on this level separately
foreach(file
		Box Parser Graph Algorithm)
	add_executable("test_${file}"
		"${file}.cpp"
		$<TARGET_OBJECTS:${PROJECT_NAME}_obj>
		$<TARGET_OBJECTS:test_obj>)

	add_test("${file}" "test_${file}")
endforeach(file)
