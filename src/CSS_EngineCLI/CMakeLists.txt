file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

add_executable(CSS_EngineCLI ${SOURCE_LIST})

target_link_libraries(CSS_EngineCLI PRIVATE CSS_EngineCore)
