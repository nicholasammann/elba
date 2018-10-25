add_subdirectory(CS370)
add_subdirectory(MAT362)

target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Rotate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Transform.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Model.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Rotate.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Transform.hpp
)