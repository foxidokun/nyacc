cmake_minimum_required(VERSION 3.11)
project(nyacc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(BISON)
BISON_TARGET(parser ${CMAKE_SOURCE_DIR}/gen/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.gen.cpp 
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/inc/parser.gen.h)

find_package(FLEX)
FLEX_TARGET(lexer ${CMAKE_SOURCE_DIR}/gen/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.gen.cpp)

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include(FetchContent)

# FetchContent_Declare(fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG master
# )
# FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE nyacc_sources src/*.cpp)

add_executable(nyacc ${nyacc_sources} ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})
target_include_directories(nyacc PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(nyacc fmt)
target_link_libraries(nyacc LLVM-18)

file(GLOB_RECURSE nyacclib_sources stdlib/*.cpp)
add_library(nyacclib STATIC ${nyacclib_sources})
target_link_libraries(nyacclib fmt)
