add_subdirectory(Components)

target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Component.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CoreModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Object.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Component.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CoreForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CoreModule.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CoreTypedefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Object.hpp
)
