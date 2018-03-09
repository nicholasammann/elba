target_sources(elba
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsFactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsModule.cpp
	${CMAKE_CURRENT_LIST_DIR}/PhysicsTransform.cpp

PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsFactory.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsForwardDeclarations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PhysicsModule.hpp
	${CMAKE_CURRENT_LIST_DIR}/PhysicsTransform.hpp
)
