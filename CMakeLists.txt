cmake_minimum_required(VERSION 3.12.1 FATAL_ERROR)

project(elba CXX C)
project(editor CXX C)
project(game CXX C)

set(submodule_root ${CMAKE_CURRENT_LIST_DIR}/submodules)
set(includes_root ${CMAKE_CURRENT_LIST_DIR}/includes)
set(libs_root ${CMAKE_CURRENT_LIST_DIR}/libs)
set(bin_root ${CMAKE_CURRENT_LIST_DIR}/bin)
set(cmake_dir ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(qt_root ${CMAKE_CURRENT_LIST_DIR}/qt)

set(elba_root ${CMAKE_CURRENT_LIST_DIR}/src/Elba)
set(editor_root ${CMAKE_CURRENT_LIST_DIR}/src/Editor)

# mimic folder structure
include(${cmake_dir}/YTE_Source_Group.cmake)

add_subdirectory(submodules)
add_subdirectory(src)
