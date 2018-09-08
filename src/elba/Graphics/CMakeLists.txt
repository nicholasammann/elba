target_sources(elba
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsModule.cpp

    ${CMAKE_CURRENT_LIST_DIR}/GraphicsFactory.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GraphicsFactory.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Mesh.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Mesh.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Submesh.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Submesh.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Shader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Shader.cpp

    ${CMAKE_CURRENT_LIST_DIR}/GraphicsForwardDeclarations.hpp

    ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLModule.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLModule.cpp

    ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLWindow.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OpenGL/OpenGLWindow.cpp
)
