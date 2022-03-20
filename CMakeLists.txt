cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Scanner.h Token.h DatalogProgram.h Rule.h Predicate.h Parameter.h Parser.h Fact.h Query.h Scheme.h Tuple.h Relation.h Database.h Interpreter.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )