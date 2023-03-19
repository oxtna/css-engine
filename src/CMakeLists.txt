cmake_minimum_required(VERSION 3.19)

project(CSS_Engine
	VERSION 0.1.0
	DESCRIPTION "CSS Engine that interprets CSS markup and executes commands"
	LANGUAGES CXX
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(CSS_EngineCore)

add_subdirectory(CSS_EngineCLI)
