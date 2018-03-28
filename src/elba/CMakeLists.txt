add_library(elba "")

include(Core/CMakeLists.txt)
include(Framework/CMakeLists.txt)
include(Graphics/CMakeLists.txt)
include(Physics/CMakeLists.txt)
include(Tests/CMakeLists.txt)
include(Utilities/CMakeLists.txt)

target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Engine.cpp

#PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Engine.hpp
)

target_include_directories(elba
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${submodule_root}/glm/
    ${includes_root}
)

add_executable(game 
    "main.cpp"
)

find_package(OpenGL REQUIRED)

target_link_libraries(game
PRIVATE
    elba
    ${libs_root}/assimp.lib
    ${libs_root}/glew32.lib
    ${libs_root}/glew32s.lib
    ${libs_root}/glfw3.lib
    ${OPENGL_LIBRARIES}
)