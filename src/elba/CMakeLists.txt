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
)

add_executable(game 
    "main.cpp"
)

target_link_libraries(game
PRIVATE
    elba
)