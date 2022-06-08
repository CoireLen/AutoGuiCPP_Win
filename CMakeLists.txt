cmake_minimum_required(VERSION 3.0.0)
project(AutoGui VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(AutoGui main.cpp autogui.h autogui.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
