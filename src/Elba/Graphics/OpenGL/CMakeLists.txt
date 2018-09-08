target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLModule.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLWindow.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLModule.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLWindow.hpp
)
