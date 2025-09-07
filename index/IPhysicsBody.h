// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <memory>

namespace HeavenlyPalace {

class IShape;

/// Motion types for physics bodies
enum class MotionType {
    Static,     ///< Non-movable body
    Kinematic,  ///< Movable using velocities only, doesn't respond to forces
    Dynamic     ///< Responds to forces as a normal physics object
};

/// Abstract interface for a physics body (rigid body)
class IPhysicsBody {
public:
    virtual ~IPhysicsBody() = default;

    /// Get the unique identifier for this body
    /// @return Body ID
    virtual uint32_t GetID() const = 0;

    /// Set position of the body
    /// @param position New position in world space
    virtual void SetPosition(const Vec3& position) = 0;

    /// Get position of the body
    /// @return Position in world space
    virtual Vec3 GetPosition() const = 0;

    /// Set rotation of the body
    /// @param rotation New rotation as quaternion
    virtual void SetRotation(const Quaternion& rotation) = 0;

    /// Get rotation of the body
    /// @return Rotation as quaternion
    virtual Quaternion GetRotation() const = 0;

    /// Set linear velocity
    /// @param velocity Linear velocity vector
    virtual void SetLinearVelocity(const Vec3& velocity) = 0;

    /// Get linear velocity
    /// @return Linear velocity vector
    virtual Vec3 GetLinearVelocity() const = 0;

    /// Set angular velocity
    /// @param velocity Angular velocity vector
    virtual void SetAngularVelocity(const Vec3& velocity) = 0;

    /// Get angular velocity
    /// @return Angular velocity vector
    virtual Vec3 GetAngularVelocity() const = 0;

    /// Apply force to the body at its center of mass
    /// @param force Force vector to apply
    virtual void AddForce(const Vec3& force) = 0;

    /// Apply force to the body at a specific point
    /// @param force Force vector to apply
    /// @param point Point in world space where to apply the force
    virtual void AddForceAtPoint(const Vec3& force, const Vec3& point) = 0;

    /// Apply torque to the body
    /// @param torque Torque vector to apply
    virtual void AddTorque(const Vec3& torque) = 0;

    /// Set the motion type of the body
    /// @param motionType New motion type
    virtual void SetMotionType(MotionType motionType) = 0;

    /// Get the motion type of the body
    /// @return Current motion type
    virtual MotionType GetMotionType() const = 0;

    /// Set the collision shape
    /// @param shape New collision shape
    virtual void SetShape(std::shared_ptr<IShape> shape) = 0;

    /// Get the collision shape
    /// @return Current collision shape
    virtual std::shared_ptr<IShape> GetShape() const = 0;

    /// Set mass properties
    /// @param mass Mass in kg (0 for infinite mass)
    virtual void SetMass(float mass) = 0;

    /// Get mass
    /// @return Mass in kg (0 for infinite mass)
    virtual float GetMass() const = 0;

    /// Activate the body (wake it up from sleep)
    virtual void Activate() = 0;

    /// Deactivate the body (put it to sleep)
    virtual void Deactivate() = 0;

    /// Check if the body is active
    /// @return True if active, false if sleeping
    virtual bool IsActive() const = 0;

    /// Set whether this body can go to sleep
    /// @param canSleep True if body can sleep, false otherwise
    virtual void SetCanSleep(bool canSleep) = 0;

    /// Check if this body can go to sleep
    /// @return True if body can sleep, false otherwise
    virtual bool CanSleep() const = 0;
};

} // namespace HeavenlyPalace