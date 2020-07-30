add_executable(Sandbox)

target_link_libraries( Sandbox
		PUBLIC
		$<$<CONFIG:Debug>:gcov>
		SFML_Framework )

target_compile_features( Sandbox
		PUBLIC
		cxx_std_20 )
target_compile_options( Sandbox
		PUBLIC
		-Wall
		-Wextra
		$<$<CONFIG:Release>: -O2 >
		$<$<CONFIG:Debug>: -O0 --coverage -fPIC > )

add_custom_command(	TARGET Sandbox
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/resources/
		${CMAKE_CURRENT_BINARY_DIR}/resources/ )

target_sources(Sandbox
		PUBLIC
		main.cpp
		testGame.cpp
		testState.cpp)