target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/FuzzySet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PiecewiseLinear.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TakagiSugenoSystem.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/FuzzySet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PiecewiseLinear.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TakagiSugenoSystem.hpp
)
