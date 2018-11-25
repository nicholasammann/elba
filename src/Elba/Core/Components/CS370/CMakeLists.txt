target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/ImageOperationHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RealtimeHatching.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ResizeHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/VideoTransitions.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ImageOperationHandler.hpp
    ${CMAKE_CURRENT_LIST_DIR}/RealtimeHatching.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ResizeHandler.hpp
    ${CMAKE_CURRENT_LIST_DIR}/VideoTransitions.hpp
)