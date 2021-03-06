set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_executable(editor)
set_property(TARGET editor PROPERTY CXX_STANDARD 17)

# Include all subdirectories
add_subdirectory(Framework)
add_subdirectory(LevelEditor)
add_subdirectory(ImageEditor)

# Add main source file
target_sources(editor
PRIVATE
  main.cpp
)

# Joshua T. Fisher's function for mimicking directories in VS solution
YTE_Source_Group(CMAKE_CURRENT_LIST_DIR editor)

# Add directories to include path
target_include_directories(editor
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${elba_root}/../
  ${submodules_root}/rapidjson/include/
  ${qt_root}/include
  ${qt_root}/include/QtCore
  ${qt_root}/include/QtGui
  ${qt_root}/include/QtWidgets
)

# Make sure OpenGL is present
find_package(OpenGL REQUIRED)

# Link to all libs necessary for editor and engine
target_link_libraries(editor
PRIVATE
  elba
  ${libs_root}/assimp-vc140-mt.lib
  ${libs_root}/glew32.lib
  ${libs_root}/glew32s.lib
  ${libs_root}/glfw3.lib

  ${OPENGL_LIBRARIES}
  ${qt_root}/lib/Qt5Core.lib
  ${qt_root}/lib/Qt5Gui.lib
  ${qt_root}/lib/Qt5Widgets.lib
)

# Post-build step for copying dll's to same folder as exe
add_custom_command(TARGET editor POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${dlls_root}/elba/ ${editor_out}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${dlls_root}/editor_only/ ${editor_out}
)

#if (${build_type} STREQUAL Debug)
#  add_custom_command(TARGET editor POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Core.pdb ${editor_out}/Qt5Core.pdb
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Gui.pdb ${editor_out}/Qt5Gui.pdb
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${qt_root}/bin/Qt5Widgets.pdb ${editor_out}/Qt5Widgets.pdb
#  )
#endif()
