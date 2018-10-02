add_subdirectory(CS370)

target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Factory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Shader.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Submesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Texture.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PostProcessingBuffer.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Factory.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Mesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/OpenGLModule.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Shader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Submesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Texture.hpp
  ${CMAKE_CURRENT_LIST_DIR}/PostProcessingBuffer.hpp
)
