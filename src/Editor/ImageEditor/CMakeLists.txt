add_subdirectory(ImageWindow)
add_subdirectory(Menus)
add_subdirectory(OptionsPanel)

target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/ImageEditor.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/ImageEditor.hpp
)