cmake_minimum_required(VERSION 3.20)
project(versionadorlp1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(versionadorlp1 main.cpp)
target_include_directories(versionadorlp1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
