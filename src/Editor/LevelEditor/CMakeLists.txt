add_subdirectory(LevelWindow)
add_subdirectory(Menus)
add_subdirectory(ObjectBrowser)
add_subdirectory(PostProcessingOptions)

target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/LevelEditor.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/LevelEditor.hpp
)