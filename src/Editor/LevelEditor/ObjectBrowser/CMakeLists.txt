target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/ObjectBrowser.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ObjectTree.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/ObjectBrowser.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ObjectTree.hpp
)