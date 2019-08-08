target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Module.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Resource.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceManager.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/FrameworkForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Module.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Resource.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResourceManager.hpp
)
