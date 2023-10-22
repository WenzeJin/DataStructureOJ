cmake_minimum_required(VERSION 3.5.0)
project(DataStructureOJ VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

add_executable(DataStructureOJ 
                main.cpp 
                )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
