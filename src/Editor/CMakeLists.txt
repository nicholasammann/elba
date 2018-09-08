add_executable(editor)

include(Framework/CMakeLists.txt)
include(LevelEditor/CMakeLists.txt)

target_sources(editor
PRIVATE
  main.cpp
)

YTE_Source_Group(CMAKE_CURRENT_LIST_DIR editor)

target_include_directories(editor
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${elba_root}/../
  ${qt_root}/include
  ${qt_root}/include/QtCore
  ${qt_root}/include/QtGui
  ${qt_root}/include/QtWidgets
)

find_package(OpenGL REQUIRED)

target_link_libraries(editor
PRIVATE
    elba
    ${libs_root}/assimp.lib
    ${libs_root}/glew32.lib
    ${libs_root}/glew32s.lib
    ${libs_root}/glfw3.lib
    ${OPENGL_LIBRARIES}

    ${qt_root}/lib/Qt5Core.lib
    ${qt_root}/lib/Qt5Gui.lib
    ${qt_root}/lib/Qt5Widgets.lib
)

add_custom_command(TARGET editor POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different

  # file to copy
  ${bin_root}/glew32.dll

  # output file
  ${editor_out}/glew32.dll
)

add_custom_command(TARGET editor POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${bin_root}/glew32.dll ${editor_out}/glew32.dll
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Core.dll ${editor_out}/Qt5Core.dll
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Gui.dll ${editor_out}/Qt5Gui.dll
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Widgets.dll ${editor_out}/Qt5Widgets.dll
)

#if (${build_type} STREQUAL Debug)
#  add_custom_command(TARGET editor POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Core.pdb ${editor_out}/Qt5Core.pdb
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Gui.pdb ${editor_out}/Qt5Gui.pdb
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Widgets.pdb ${editor_out}/Qt5Widgets.pdb
#  )
#endif()
