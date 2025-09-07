// Heavenly Palace Physics - Jolt Physics Engine Implementation
// SPDX-License-Identifier: MIT
#pragma once

#include "../IPhysicsBody.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>

// Forward declarations
JPH_NAMESPACE_BEGIN
class Body;
class BodyInterface;
JPH_NAMESPACE_END

namespace HeavenlyPalace {

class IShape;
class JoltPhysicsWorld;

/// Jolt Physics implementation of IPhysicsBody
class JoltPhysicsBody : public IPhysicsBody {
public:
    JoltPhysicsBody(JoltPhysicsWorld* world, JPH::BodyID bodyId);
    virtual ~JoltPhysicsBody();

    // IPhysicsBody interface implementation
    uint32_t GetID() const override;
    void SetPosition(const Vec3& position) override;
    Vec3 GetPosition() const override;
    void SetRotation(const Quaternion& rotation) override;
    Quaternion GetRotation() const override;
    void SetLinearVelocity(const Vec3& velocity) override;
    Vec3 GetLinearVelocity() const override;
    void SetAngularVelocity(const Vec3& velocity) override;
    Vec3 GetAngularVelocity() const override;
    void AddForce(const Vec3& force) override;
    void AddForceAtPoint(const Vec3& force, const Vec3& point) override;
    void AddTorque(const Vec3& torque) override;
    void SetMotionType(MotionType motionType) override;
    MotionType GetMotionType() const override;
    void SetShape(std::shared_ptr<IShape> shape) override;
    std::shared_ptr<IShape> GetShape() const override;
    void SetMass(float mass) override;
    float GetMass() const override;
    void Activate() override;
    void Deactivate() override;
    bool IsActive() const override;
    void SetCanSleep(bool canSleep) override;
    bool CanSleep() const override;

    /// Get the underlying Jolt body ID
    JPH::BodyID GetJoltBodyID() const { return m_bodyId; }

private:
    JoltPhysicsWorld* m_world;
    JPH::BodyID m_bodyId;
    std::shared_ptr<IShape> m_shape;
    
    /// Get the Jolt body interface from the world
    JPH::BodyInterface& GetBodyInterface() const;
    
    /// Convert Heavenly Palace motion type to Jolt motion type
    static JPH::EMotionType ToJoltMotionType(MotionType motionType);
    
    /// Convert Jolt motion type to Heavenly Palace motion type
    static MotionType FromJoltMotionType(JPH::EMotionType motionType);
};

} // namespace HeavenlyPalace