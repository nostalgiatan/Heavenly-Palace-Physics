// Heavenly Palace Physics - Box2D Physics Engine Implementation
// SPDX-License-Identifier: MIT
#pragma once

#include "../IPhysicsBody.h"
#include <memory>

// Forward declare Box2D types
struct b2Body;

namespace HeavenlyPalace {

/// Box2D implementation of IPhysicsBody
/// Note: Box2D is a 2D physics engine, so Z components will be ignored/set to 0
class Box2DPhysicsBody : public IPhysicsBody {
public:
    Box2DPhysicsBody(b2Body* body);
    virtual ~Box2DPhysicsBody();

    // IPhysicsBody interface implementation
    uint32_t GetID() const override;
    
    void SetPosition(const Vec3& position) override;
    Vec3 GetPosition() const override;
    
    void SetRotation(const Quaternion& rotation) override;
    Quaternion GetRotation() const override;
    
    void SetLinearVelocity(const Vec3& velocity) override;
    Vec3 GetLinearVelocity() const override;
    
    void SetAngularVelocity(const Vec3& angularVelocity) override;
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

    /// Get the underlying Box2D body (for advanced usage)
    /// @return Box2D body instance
    b2Body* GetBox2DBody() const { return m_body; }

private:
    b2Body* m_body = nullptr;
    std::shared_ptr<IShape> m_shape;
    void* m_userData = nullptr;
};

} // namespace HeavenlyPalace