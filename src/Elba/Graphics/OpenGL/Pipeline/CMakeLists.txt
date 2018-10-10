target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLComputeShader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLFragmentShader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLPostProcessBuffer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLShader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLProgram.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLVertexShader.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLComputeShader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLFragmentShader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLPostProcessBuffer.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLShader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLProgram.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLVertexShader.hpp
)
