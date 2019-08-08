cmake_minimum_required(VERSION 3.10.3 FATAL_ERROR)

project(elba CXX C)

set(submodules_root ${CMAKE_CURRENT_LIST_DIR}/submodules)
set(includes_root ${CMAKE_CURRENT_LIST_DIR}/includes)
set(libs_root ${CMAKE_CURRENT_LIST_DIR}/libs)
set(dlls_root ${CMAKE_CURRENT_LIST_DIR}/dlls)
set(cmake_dir ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(qt_root ${CMAKE_CURRENT_LIST_DIR}/qt)

set(elba_root ${CMAKE_CURRENT_LIST_DIR}/src/Elba)
set(editor_root ${CMAKE_CURRENT_LIST_DIR}/src/Editor)

set(build_type $<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>)

set(elba_out ${CMAKE_CURRENT_LIST_DIR}/build/src/elba/${build_type})
set(editor_out ${CMAKE_CURRENT_LIST_DIR}/build/src/editor/${build_type})

# Include funtion for mimicking folder structure
include(${cmake_dir}/YTE_Source_Group.cmake)

add_subdirectory(submodules)
add_subdirectory(src)
