add_subdirectory(CS370)
add_subdirectory(Pipeline)

target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLMesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLSubmesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLTexture.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLFactory.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLMesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLSubmesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLTexture.hpp
)
