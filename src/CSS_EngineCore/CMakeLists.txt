file(GLOB HEADER_LIST CONFIGURE_DEPENDS "include/*.(h|hxx)")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "*.cpp")

add_library(CSS_EngineCore STATIC)

target_sources(CSS_EngineCore
	PRIVATE
		${SOURCE_LIST}
	PUBLIC
		${HEADER_LIST}
)

target_include_directories(CSS_EngineCore PUBLIC include)
