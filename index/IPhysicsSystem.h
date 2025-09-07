// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <memory>

namespace HeavenlyPalace {

// Forward declarations
class IPhysicsWorld;
class IPhysicsBody;
class IShape;
class IBoxShape;
class ISphereShape;
class ICapsuleShape;
class IMeshShape;
class ICompoundShape;

/// Factory for creating physics objects
/// This provides a unified way to create physics objects regardless of the underlying engine
class IPhysicsFactory {
public:
    virtual ~IPhysicsFactory() = default;

    /// Create a physics world
    /// @return New physics world instance
    virtual std::shared_ptr<IPhysicsWorld> CreatePhysicsWorld() = 0;

    /// Create a box shape
    /// @param halfExtents Half extents of the box (half width, half height, half depth)
    /// @return New box shape instance
    virtual std::shared_ptr<IBoxShape> CreateBoxShape(const Vec3& halfExtents) = 0;

    /// Create a sphere shape
    /// @param radius Radius of the sphere
    /// @return New sphere shape instance
    virtual std::shared_ptr<ISphereShape> CreateSphereShape(float radius) = 0;

    /// Create a capsule shape
    /// @param radius Radius of the capsule
    /// @param height Height of the cylindrical part (excluding caps)
    /// @return New capsule shape instance
    virtual std::shared_ptr<ICapsuleShape> CreateCapsuleShape(float radius, float height) = 0;

    /// Create a mesh shape from vertices and indices
    /// @param vertices Array of vertex positions
    /// @param vertexCount Number of vertices
    /// @param indices Array of triangle indices (3 per triangle)
    /// @param indexCount Number of indices
    /// @return New mesh shape instance
    virtual std::shared_ptr<IMeshShape> CreateMeshShape(const Vec3* vertices, uint32_t vertexCount,
                                                        const uint32_t* indices, uint32_t indexCount) = 0;

    /// Create a compound shape
    /// @return New compound shape instance
    virtual std::shared_ptr<ICompoundShape> CreateCompoundShape() = 0;

    /// Get the physics engine type this factory creates
    /// @return Physics engine type
    virtual PhysicsEngineType GetEngineType() const = 0;
};

/// Main physics system interface
/// This is the primary entry point for physics operations
class IPhysicsSystem {
public:
    virtual ~IPhysicsSystem() = default;

    /// Initialize the physics system
    /// @param engineType Type of physics engine to use
    /// @return True if initialization succeeded
    virtual bool Initialize(PhysicsEngineType engineType = PhysicsEngineType::Jolt) = 0;

    /// Shutdown the physics system
    virtual void Shutdown() = 0;

    /// Get the factory for creating physics objects
    /// @return Physics factory interface
    virtual IPhysicsFactory* GetFactory() = 0;

    /// Get the currently active physics world
    /// @return Current physics world, nullptr if none
    virtual std::shared_ptr<IPhysicsWorld> GetWorld() = 0;

    /// Set the active physics world
    /// @param world New physics world to use
    virtual void SetWorld(std::shared_ptr<IPhysicsWorld> world) = 0;

    /// Perform a raycast in the current world
    /// @param origin Starting point of the ray
    /// @param direction Direction of the ray (will be normalized)
    /// @param maxDistance Maximum distance to cast
    /// @return Raycast result
    virtual RaycastResult Raycast(const Vec3& origin, const Vec3& direction, float maxDistance = 1000.0f) = 0;

    /// Check if the physics system is initialized
    /// @return True if initialized, false otherwise
    virtual bool IsInitialized() const = 0;

    /// Get the current physics engine type
    /// @return Physics engine type
    virtual PhysicsEngineType GetEngineType() const = 0;
};

/// Enhanced physics manager with plugin support
/// This provides a singleton-like interface with automatic plugin management
class PhysicsManager {
public:
    /// Get the global physics system instance
    /// @return Physics system instance, nullptr if not created
    static IPhysicsSystem* GetInstance();

    /// Create and initialize the physics system using plugin architecture
    /// @param engineType Type of physics engine to use
    /// @return True if creation and initialization succeeded
    static bool CreateSystem(PhysicsEngineType engineType = PhysicsEngineType::Jolt);

    /// Destroy the physics system
    static void DestroySystem();

    /// Check if the physics system exists and is initialized
    /// @return True if system is ready for use
    static bool IsReady();

    /// Get list of all available physics engines (from plugin registry)
    /// @param count Output parameter for number of engines
    /// @return Array of available engine types
    static const PhysicsEngineType* GetAvailableEngines(uint32_t& count);

    /// Get plugin information for a specific engine
    /// @param engineType Engine type to query
    /// @return Plugin information or nullptr if not available
    static const PluginInfo* GetEngineInfo(PhysicsEngineType engineType);

    /// Switch to a different physics engine (experimental)
    /// @param engineType New engine type to switch to
    /// @param preserveState Whether to attempt state preservation
    /// @return True if switch succeeded
    static bool SwitchEngine(PhysicsEngineType engineType, bool preserveState = false);

    /// Initialize all available physics engine plugins
    /// @return True if all plugins initialized successfully
    static bool InitializePlugins();

    /// Shutdown all plugins
    static void ShutdownPlugins();

    /// Check if an engine type is supported on current platform
    /// @param engineType Engine type to check
    /// @return True if supported, false otherwise
    static bool IsEngineSupported(PhysicsEngineType engineType);

private:
    static std::unique_ptr<IPhysicsSystem> s_instance;
    static PhysicsEngineType s_currentEngineType;
    static bool s_pluginsInitialized;
};

} // namespace HeavenlyPalace