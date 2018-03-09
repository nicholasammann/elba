cmake_minimum_required(VERSION 3.9.1 FATAL_ERROR)

project(elba CXX C)

set(submodule_root ${CMAKE_CURRENT_LIST_DIR}/submodules)

add_subdirectory(submodules)
add_subdirectory(src)
