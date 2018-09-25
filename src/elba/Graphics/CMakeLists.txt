add_subdirectory(OpenGL)

target_sources(elba
PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Camera.cpp
  ${CMAKE_CURRENT_LIST_DIR}/GraphicsFactory.cpp
  ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Submesh.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Camera.hpp
  ${CMAKE_CURRENT_LIST_DIR}/GraphicsFactory.hpp
  ${CMAKE_CURRENT_LIST_DIR}/GraphicsForwardDeclarations.hpp
  ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Mesh.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Submesh.hpp
)
