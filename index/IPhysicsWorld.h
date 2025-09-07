// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <memory>

namespace HeavenlyPalace {

// Forward declarations
class IPhysicsBody;

/// Abstract interface for a physics world/system
/// This provides a unified interface across different physics engines
class IPhysicsWorld {
public:
    virtual ~IPhysicsWorld() = default;

    /// Initialize the physics world
    /// @param maxBodies Maximum number of bodies in the simulation
    /// @param maxBodyPairs Maximum number of body pairs that can be in contact
    /// @param maxContactConstraints Maximum number of contact constraints
    virtual bool Initialize(uint32_t maxBodies, uint32_t maxBodyPairs, uint32_t maxContactConstraints) = 0;

    /// Step the physics simulation
    /// @param deltaTime Time step in seconds
    /// @param collisionSteps Number of collision detection steps
    /// @param integrationSubSteps Number of integration sub-steps
    virtual void Update(float deltaTime, int collisionSteps = 1, int integrationSubSteps = 1) = 0;

    /// Create a physics body
    /// @param bodySettings Settings for the body creation
    /// @return Shared pointer to the created body, nullptr if creation failed
    virtual std::shared_ptr<IPhysicsBody> CreateBody(const BodyCreationSettings& bodySettings) = 0;

    /// Remove a physics body from the world
    /// @param body Body to remove
    virtual void RemoveBody(std::shared_ptr<IPhysicsBody> body) = 0;

    /// Set gravity vector
    /// @param gravity Gravity vector (typically (0, -9.81, 0))
    virtual void SetGravity(const Vec3& gravity) = 0;

    /// Get gravity vector
    /// @return Current gravity vector
    virtual Vec3 GetGravity() const = 0;

    /// Enable/disable physics simulation
    /// @param enabled True to enable, false to disable
    virtual void SetEnabled(bool enabled) = 0;

    /// Check if physics simulation is enabled
    /// @return True if enabled, false otherwise
    virtual bool IsEnabled() const = 0;

    /// Cleanup and shutdown the physics world
    virtual void Shutdown() = 0;
};

} // namespace HeavenlyPalace