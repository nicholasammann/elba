target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Components/Model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Components/Transform.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Components/Model.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Components/Transform.hpp
)