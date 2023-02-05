cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(theconveyor)

add_definitions(-DESP32)

include(CMakeListsPrivate.txt)

add_executable(theconveyor.exe ${SRC_LIST} include/tools/util.h)