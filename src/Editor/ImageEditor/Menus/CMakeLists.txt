target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/FileMenu.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ImageOperationsMenu.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/FileMenu.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ImageOperationsMenu.hpp
)