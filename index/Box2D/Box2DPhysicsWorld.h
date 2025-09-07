// Heavenly Palace Physics - Box2D Physics Engine Implementation
// SPDX-License-Identifier: MIT
#pragma once

#include "../IPhysicsWorld.h"
#include "../IPhysicsBody.h"
#include <memory>

// Forward declare Box2D types to avoid including Box2D headers in public interface
struct b2WorldDef;
struct b2World;

namespace HeavenlyPalace {

/// Box2D implementation of IPhysicsWorld
/// Note: Box2D is a 2D physics engine, so Z components will be ignored/set to 0
class Box2DPhysicsWorld : public IPhysicsWorld {
public:
    Box2DPhysicsWorld();
    virtual ~Box2DPhysicsWorld();

    // IPhysicsWorld interface implementation
    bool Initialize(uint32_t maxBodies, uint32_t maxBodyPairs, uint32_t maxContactConstraints) override;
    void Shutdown() override;
    void Update(float deltaTime, int collisionSteps = 1, int integrationSubSteps = 1) override;
    
    std::shared_ptr<IPhysicsBody> CreateBody(const BodyCreationSettings& settings) override;
    void RemoveBody(std::shared_ptr<IPhysicsBody> body) override;
    
    void SetGravity(const Vec3& gravity) override;
    Vec3 GetGravity() const override;
    
    void SetEnabled(bool enabled) override;
    bool IsEnabled() const override;
    
    /// Perform a raycast (convenience method for compatibility)
    /// @param origin Starting point of the ray
    /// @param direction Direction of the ray (will be normalized)
    /// @param maxDistance Maximum distance to cast
    /// @return Raycast result
    RaycastResult Raycast(const Vec3& origin, const Vec3& direction, float maxDistance = 1000.0f);
    
    /// Check if the physics world is initialized
    /// @return True if initialized, false otherwise
    bool IsInitialized() const;
    
    /// Get the underlying Box2D world (for advanced usage)
    /// @return Box2D world instance, nullptr if not initialized
    b2World* GetBox2DWorld() const { return m_world; }

private:
    b2World* m_world = nullptr;
    bool m_initialized = false;
    bool m_enabled = true;
    Vec3 m_gravity = Vec3(0.0f, -9.81f, 0.0f);
};

} // namespace HeavenlyPalace