cmake_minimum_required(VERSION 3.9.1 FATAL_ERROR)

project(elba CXX C)

set(submodule_root ${CMAKE_CURRENT_LIST_DIR}/submodules)
set(includes_root ${CMAKE_CURRENT_LIST_DIR}/includes)
set(libs_root ${CMAKE_CURRENT_LIST_DIR}/libs)

add_subdirectory(submodules)
add_subdirectory(src)
