add_library(elba STATIC)

# Include all subdirectories
add_subdirectory(Core)
add_subdirectory(Framework)
add_subdirectory(Graphics)
add_subdirectory(Physics)
add_subdirectory(Tests)
add_subdirectory(Utilities)

# Add engine source files
target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Engine.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Engine.hpp
)

# Joshua T. Fisher's function for mimicking directories in VS solution
#YTE_Source_Group(CMAKE_CURRENT_LIST_DIR elba)

# Add necessary dirs to include path
target_include_directories(elba
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../
    ${submodules_root}/glm/
    ${submodules_root}/rapidjson/include/
    ${includes_root}
    ${bin_root}
)

# Game exe
add_executable(game 
    "main.cpp"
)

# Verify that OpenGL is available
find_package(OpenGL REQUIRED)

# Link libaries for game/engine
target_link_libraries(game
PRIVATE
    elba
    ${libs_root}/assimp-vc140-mt.lib
    ${libs_root}/glew32.lib
    ${libs_root}/glew32s.lib
    ${libs_root}/glfw3.lib
    ${OPENGL_LIBRARIES}
)

# Post-build step for copying dll's to same folder as exe
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${dlls_root}/elba/ ${elba_out}
)
