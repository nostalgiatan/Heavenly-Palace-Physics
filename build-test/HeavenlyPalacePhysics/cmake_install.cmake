# Install script for directory: /home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/HeavenlyPalacePhysics/HeavenlyPalacePhysics.h;/HeavenlyPalacePhysics/Common.h;/HeavenlyPalacePhysics/IPhysicsSystem.h;/HeavenlyPalacePhysics/IPhysicsWorld.h;/HeavenlyPalacePhysics/IPhysicsBody.h;/HeavenlyPalacePhysics/IShape.h;/HeavenlyPalacePhysics/JoltPhysicsSystem.h;/HeavenlyPalacePhysics/JoltPhysicsWorld.h;/HeavenlyPalacePhysics/JoltPhysicsBody.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/HeavenlyPalacePhysics" TYPE FILE FILES
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/HeavenlyPalacePhysics.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Common.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/IPhysicsSystem.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/IPhysicsWorld.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/IPhysicsBody.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/IShape.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsSystem.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsWorld.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsBody.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/HeavenlyPalacePhysics/Jolt/JoltPhysicsSystem.h;/HeavenlyPalacePhysics/Jolt/JoltPhysicsWorld.h;/HeavenlyPalacePhysics/Jolt/JoltPhysicsBody.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/HeavenlyPalacePhysics/Jolt" TYPE FILE FILES
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsSystem.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsWorld.h"
    "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/index/Jolt/JoltPhysicsBody.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/runner/work/Heavenly-Palace-Physics/Heavenly-Palace-Physics/build-test/HeavenlyPalacePhysics/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
