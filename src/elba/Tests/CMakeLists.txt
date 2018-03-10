target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/CoreTests.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsTests.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CoreTests.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsTests.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TestHelpers.hpp
)
