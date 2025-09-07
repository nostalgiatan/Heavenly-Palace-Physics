# Heavenly Palace Physics - Universal Physics Engine Abstraction
# CMake configuration for the abstraction layer

cmake_minimum_required(VERSION 3.20)

project(HeavenlyPalacePhysics VERSION 1.0.0 LANGUAGES CXX)

# Define the abstraction layer library
set(HEAVENLY_PALACE_PHYSICS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all header files
set(HEAVENLY_PALACE_HEADERS
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/HeavenlyPalacePhysics.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Common.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/IPhysicsSystem.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/IPhysicsWorld.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/IPhysicsBody.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/IShape.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/IPhysicsPlugin.h
)

# Collect source files
set(HEAVENLY_PALACE_SOURCES
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/HeavenlyPalacePhysics.cpp
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Common.cpp
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/PhysicsPluginRegistry.cpp
)

# Jolt implementation headers
set(HEAVENLY_PALACE_JOLT_HEADERS
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Jolt/JoltPhysicsSystem.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Jolt/JoltPhysicsWorld.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Jolt/JoltPhysicsBody.h
)

# Box2D implementation headers
set(HEAVENLY_PALACE_BOX2D_HEADERS
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsSystem.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsWorld.h
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsBody.h
)

# Box2D implementation sources
set(HEAVENLY_PALACE_BOX2D_SOURCES
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsSystem.cpp
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsWorld.cpp
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPhysicsBody.cpp
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Box2D/Box2DPlugin.cpp
)

# Jolt implementation sources
set(HEAVENLY_PALACE_JOLT_SOURCES
    ${HEAVENLY_PALACE_PHYSICS_ROOT}/Jolt/JoltPlugin.cpp
    # Additional Jolt implementation files would go here
)

# Add all files to the library sources
list(APPEND HEAVENLY_PALACE_HEADERS ${HEAVENLY_PALACE_JOLT_HEADERS})
list(APPEND HEAVENLY_PALACE_HEADERS ${HEAVENLY_PALACE_BOX2D_HEADERS})
list(APPEND HEAVENLY_PALACE_SOURCES ${HEAVENLY_PALACE_BOX2D_SOURCES})
list(APPEND HEAVENLY_PALACE_SOURCES ${HEAVENLY_PALACE_JOLT_SOURCES})

# Create interface library for headers only (until we implement the Jolt backend)
add_library(HeavenlyPalacePhysics INTERFACE)

# Set include directories
target_include_directories(HeavenlyPalacePhysics INTERFACE
    ${HEAVENLY_PALACE_PHYSICS_ROOT}
)

# Check if Box2D is available as a submodule
set(BOX2D_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/box2d)
if(EXISTS ${BOX2D_ROOT}/CMakeLists.txt)
    # Add Box2D subdirectory
    add_subdirectory(${BOX2D_ROOT} box2d EXCLUDE_FROM_ALL)
    
    # Link against Box2D when available
    if(TARGET box2d)
        target_link_libraries(HeavenlyPalacePhysics INTERFACE box2d)
        target_compile_definitions(HeavenlyPalacePhysics INTERFACE HEAVENLY_PALACE_BOX2D_ENABLED)
        message(STATUS "Box2D support enabled")
    endif()
else()
    message(STATUS "Box2D not found, Box2D backend will be disabled")
endif()

# Link against Jolt Physics when available
if(TARGET Jolt)
    target_link_libraries(HeavenlyPalacePhysics INTERFACE Jolt)
endif()

# Set C++ standard
target_compile_features(HeavenlyPalacePhysics INTERFACE cxx_std_17)

# Group files for IDEs
source_group("Header Files" FILES ${HEAVENLY_PALACE_HEADERS})
source_group("Source Files" FILES ${HEAVENLY_PALACE_SOURCES})
source_group("Header Files\\Jolt" FILES ${HEAVENLY_PALACE_JOLT_HEADERS})
source_group("Header Files\\Box2D" FILES ${HEAVENLY_PALACE_BOX2D_HEADERS})
source_group("Source Files\\Box2D" FILES ${HEAVENLY_PALACE_BOX2D_SOURCES})

# Make the headers available to parent projects
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(HEAVENLY_PALACE_PHYSICS_INCLUDE_DIR ${HEAVENLY_PALACE_PHYSICS_ROOT})
else()
    set(HEAVENLY_PALACE_PHYSICS_INCLUDE_DIR ${HEAVENLY_PALACE_PHYSICS_ROOT} PARENT_SCOPE)
endif()

# Install the headers
if(ENABLE_INSTALL)
    install(FILES ${HEAVENLY_PALACE_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/HeavenlyPalacePhysics
    )
    install(FILES ${HEAVENLY_PALACE_JOLT_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/HeavenlyPalacePhysics/Jolt
    )
    install(FILES ${HEAVENLY_PALACE_BOX2D_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/HeavenlyPalacePhysics/Box2D
    )
endif()

# Create a simple test to validate the interface compiles
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR OR BUILD_TESTING)
    add_executable(HeavenlyPalacePhysicsTest
        ${HEAVENLY_PALACE_PHYSICS_ROOT}/test_interface.cpp
        ${HEAVENLY_PALACE_SOURCES}
    )
    
    target_include_directories(HeavenlyPalacePhysicsTest PRIVATE
        ${HEAVENLY_PALACE_PHYSICS_ROOT}
    )
    
    if(TARGET Jolt)
        target_link_libraries(HeavenlyPalacePhysicsTest PRIVATE Jolt)
    endif()
    
    target_compile_features(HeavenlyPalacePhysicsTest PRIVATE cxx_std_17)
    
    # Add test to CTest if available
    if(CMAKE_TESTING_ENABLED OR BUILD_TESTING)
        enable_testing()
        add_test(NAME HeavenlyPalacePhysicsInterfaceTest COMMAND HeavenlyPalacePhysicsTest)
    endif()
endif()