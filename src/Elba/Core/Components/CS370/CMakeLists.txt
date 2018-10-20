target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/ImageOperationHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ResizeHandler.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ImageOperationHandler.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResizeHandler.hpp
)