add_executable(CSS_EngineCLI)

target_link_libraries(CSS_EngineCLI PRIVATE CSS_EngineCore)

target_include_directories(CSS_EngineCLI PRIVATE include)

target_sources(CSS_EngineCLI
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
)
