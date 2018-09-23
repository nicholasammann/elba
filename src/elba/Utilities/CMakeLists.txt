target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/GlobalKey.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Utils.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/GlobalKey.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StdTypedefs.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Utils.hpp
)
