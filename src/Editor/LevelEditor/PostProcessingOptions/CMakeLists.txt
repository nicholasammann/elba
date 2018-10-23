target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/AddEffectContextMenu.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PostProcessingOptions.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/AddEffectContextMenu.hpp
  ${CMAKE_CURRENT_LIST_DIR}/PostProcessingOptions.hpp
)