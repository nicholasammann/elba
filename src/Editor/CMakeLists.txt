add_executable(editor)

include(Framework/CMakeLists.txt)

target_sources(editor
PRIVATE
  main.cpp
)

target_include_directories(editor
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${qt_root}/include
  ${qt_root}/include/QtCore
  ${qt_root}/include/QtGui
  ${qt_root}/include/QtWidgets
)

target_link_libraries(editor
PRIVATE
    ${qt_root}/lib/Qt5Core.lib
    ${qt_root}/lib/Qt5Gui.lib
    ${qt_root}/lib/Qt5Widgets.lib
)
