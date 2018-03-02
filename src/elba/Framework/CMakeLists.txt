target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Module.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/FrameworkForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Module.hpp
)
