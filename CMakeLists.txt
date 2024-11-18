cmake_minimum_required(VERSION 3.11)
project(nyacc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(BISON)
BISON_TARGET(parser ${CMAKE_SOURCE_DIR}/gen/parser.y ${CMAKE_SOURCE_DIR}/src/parser.gen.cpp 
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/inc/parser.gen.h)

find_package(FLEX)
FLEX_TARGET(lexer ${CMAKE_SOURCE_DIR}/gen/lexer.l ${CMAKE_SOURCE_DIR}/src/lexer.gen.cpp 
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/inc/lexer.gen.h)

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE sources src/*.cpp src/*.h)

# Build fully static
add_executable(validator ${sources} ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})
target_include_directories(validator PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(validator fmt::fmt)
