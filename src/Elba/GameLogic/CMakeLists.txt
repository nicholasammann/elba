add_subdirectory(CS370)
add_subdirectory(MAT362)

target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Rotate.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Rotate.hpp
)
