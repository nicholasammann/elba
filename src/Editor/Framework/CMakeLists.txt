################################################################################
## This source file is a part of YTEditor.
## Legal  : All content (c) 2016 DigiPen  (USA) Corporation, all rights reserved.
## Author : Nicholas Ammann
################################################################################

target_sources(editor
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/MainWindow.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Menu.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ToolBar.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Widget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Workspace.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/MainWindow.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Menu.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ToolBar.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Widget.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Workspace.hpp
)
