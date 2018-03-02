target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.hpp
)
