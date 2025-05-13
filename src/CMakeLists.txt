bison_target(SqlParser sql.ypp sql_tab.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/sql_tab.hpp)
flex_target(SqlLexer sql.l sql_lexer.yy.cpp DEFINES_FILE sql_lexer.yy.hpp)
add_flex_bison_dependency(SqlLexer SqlParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(visenten ${BISON_SqlParser_OUTPUTS} ${FLEX_SqlLexer_OUTPUTS})
target_include_directories(visenten PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Not needed?
# target_link_libraries(visenten ${FLEX_LIBRARIES})
