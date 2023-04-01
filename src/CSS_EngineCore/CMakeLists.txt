file(GLOB HEADER_LIST CONFIGURE_DEPENDS "include/*.(h|hxx)")

add_library(CSS_EngineCore STATIC)

set_property(TARGET CSS_EngineCore PROPERTY CXX_STANDARD 11)

target_include_directories(CSS_EngineCore PUBLIC include)

target_sources(CSS_EngineCore
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/String.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Token.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Section.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Attribute.cpp
)

