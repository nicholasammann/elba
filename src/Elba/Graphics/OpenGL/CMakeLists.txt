target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLShader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLSubmesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLWindow.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLShader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLSubmesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLWindow.hpp
)
