cmake_minimum_required(VERSION 3.0.0)
project(bufferProject VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

add_executable(bufferProject main.cpp gen.cpp)
target_compile_features(bufferProject PRIVATE cxx_std_20)
target_compile_options(bufferProject PRIVATE -pedantic -Wall -Werror -O0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
