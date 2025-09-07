// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

/// Main header for Heavenly Palace Physics abstraction layer
/// Include this header to access all physics interfaces

// Core types and utilities
#include "Common.h"

// Abstract interfaces  
#include "IShape.h"
#include "IPhysicsBody.h"
#include "IPhysicsWorld.h"
#include "IPhysicsSystem.h"

// Plugin system
#include "IPhysicsPlugin.h"

/// Heavenly Palace Physics provides a unified interface for physics engines
/// allowing you to switch between different physics backends (Jolt, Bullet, PhysX)
/// while maintaining the same API.
///
/// Quick start example:
/// ```cpp
/// using namespace HeavenlyPalace;
/// 
/// // Initialize physics system
/// if (!PhysicsManager::CreateSystem(PhysicsEngineType::Jolt)) {
///     // Handle error
///     return false;
/// }
/// 
/// // Get factory and create world
/// auto factory = PhysicsManager::GetInstance().GetFactory();
/// auto world = factory->CreatePhysicsWorld();
/// world->Initialize(1024, 1024, 1024);
/// world->SetGravity(Vec3(0, -9.81f, 0));
/// PhysicsManager::GetInstance().SetWorld(world);
/// 
/// // Create a box shape and body
/// auto boxShape = factory->CreateBoxShape(Vec3(1, 1, 1));
/// BodyCreationSettings settings;
/// settings.position = Vec3(0, 10, 0);
/// auto body = world->CreateBody(settings);
/// body->SetShape(boxShape);
/// 
/// // Run simulation
/// while (running) {
///     world->Update(1.0f / 60.0f);
///     // ... render, etc
/// }
/// 
/// // Cleanup
/// PhysicsManager::DestroySystem();
/// ```

namespace HeavenlyPalace {

/// Version information
constexpr int VERSION_MAJOR = 1;
constexpr int VERSION_MINOR = 0;
constexpr int VERSION_PATCH = 0;

/// Get version string
const char* GetVersionString();

/// Get supported physics engines
const PhysicsEngineType* GetSupportedEngines(uint32_t& count);

/// Check if a physics engine is supported
bool IsEngineSupported(PhysicsEngineType engineType);

} // namespace HeavenlyPalace