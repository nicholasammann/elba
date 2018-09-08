add_subdirectory(LevelWindow/CMakeLists.txt)

target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/LevelEditor.cpp

  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/LevelEditor.hpp
)