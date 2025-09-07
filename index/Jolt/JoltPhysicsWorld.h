// Heavenly Palace Physics - Jolt Physics Engine Implementation
// SPDX-License-Identifier: MIT
#pragma once

#include "../IPhysicsWorld.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <memory>

// Forward declarations
JPH_NAMESPACE_BEGIN
class TempAllocatorImpl;
class JobSystemThreadPool;
class BroadPhaseLayerInterface;
class ObjectVsBroadPhaseLayerFilter;
class ObjectLayerPairFilter;
JPH_NAMESPACE_END

namespace HeavenlyPalace {

class JoltPhysicsBody;

/// Jolt Physics implementation of IPhysicsWorld
class JoltPhysicsWorld : public IPhysicsWorld {
public:
    JoltPhysicsWorld();
    virtual ~JoltPhysicsWorld();

    // IPhysicsWorld interface implementation
    bool Initialize(uint32_t maxBodies, uint32_t maxBodyPairs, uint32_t maxContactConstraints) override;
    void Update(float deltaTime, int collisionSteps = 1, int integrationSubSteps = 1) override;
    std::shared_ptr<IPhysicsBody> CreateBody(const BodyCreationSettings& bodySettings) override;
    void RemoveBody(std::shared_ptr<IPhysicsBody> body) override;
    void SetGravity(const Vec3& gravity) override;
    Vec3 GetGravity() const override;
    void SetEnabled(bool enabled) override;
    bool IsEnabled() const override;
    void Shutdown() override;

    /// Get the underlying Jolt physics system (for advanced users)
    JPH::PhysicsSystem* GetJoltPhysicsSystem() { return m_physicsSystem.get(); }

private:
    // Jolt objects
    std::unique_ptr<JPH::TempAllocatorImpl> m_tempAllocator;
    std::unique_ptr<JPH::JobSystemThreadPool> m_jobSystem;
    std::unique_ptr<JPH::PhysicsSystem> m_physicsSystem;
    
    // Layer interfaces for Jolt
    std::unique_ptr<JPH::BroadPhaseLayerInterface> m_broadPhaseLayerInterface;
    std::unique_ptr<JPH::ObjectVsBroadPhaseLayerFilter> m_objectVsBroadPhaseLayerFilter;
    std::unique_ptr<JPH::ObjectLayerPairFilter> m_objectLayerPairFilter;
    
    bool m_initialized = false;
    bool m_enabled = true;
    uint32_t m_nextBodyId = 1;
    
    /// Initialize Jolt physics library (global initialization)
    static bool InitializeJolt();
    
    /// Shutdown Jolt physics library (global shutdown)
    static void ShutdownJolt();
    
    /// Reference count for global Jolt initialization
    static int s_joltRefCount;
};

} // namespace HeavenlyPalace