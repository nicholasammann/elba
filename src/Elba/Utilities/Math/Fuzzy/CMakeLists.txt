target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/FuzzyController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FuzzySet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PiecewiseLinear.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/FuzzyController.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FuzzySet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PiecewiseLinear.hpp
)
