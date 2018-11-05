# add check target as a convience target to invoke all checks
add_custom_target(check)

if(${FLAWFINDER})
	add_dependencies(check flawfinder)
endif()

if(${FORMAT})
	add_dependencies(check format_check)
endif()
