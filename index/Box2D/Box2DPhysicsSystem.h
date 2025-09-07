// Heavenly Palace Physics - Box2D Physics Engine Implementation
// SPDX-License-Identifier: MIT
#pragma once

#include "../IPhysicsSystem.h"
#include "Box2DPhysicsWorld.h"
#include <memory>

namespace HeavenlyPalace {

/// Box2D Physics implementation of IPhysicsFactory
class Box2DPhysicsFactory : public IPhysicsFactory {
public:
    Box2DPhysicsFactory();
    virtual ~Box2DPhysicsFactory();

    // IPhysicsFactory interface implementation
    std::shared_ptr<IPhysicsWorld> CreatePhysicsWorld() override;
    std::shared_ptr<IBoxShape> CreateBoxShape(const Vec3& halfExtents) override;
    std::shared_ptr<ISphereShape> CreateSphereShape(float radius) override;
    std::shared_ptr<ICapsuleShape> CreateCapsuleShape(float radius, float height) override;
    std::shared_ptr<IMeshShape> CreateMeshShape(const Vec3* vertices, uint32_t vertexCount,
                                                const uint32_t* indices, uint32_t indexCount) override;
    std::shared_ptr<ICompoundShape> CreateCompoundShape() override;
    PhysicsEngineType GetEngineType() const override { return PhysicsEngineType::Box2D; }
};

/// Box2D Physics implementation of IPhysicsSystem
class Box2DPhysicsSystem : public IPhysicsSystem {
public:
    Box2DPhysicsSystem();
    virtual ~Box2DPhysicsSystem();

    // IPhysicsSystem interface implementation
    bool Initialize(PhysicsEngineType engineType = PhysicsEngineType::Box2D) override;
    void Shutdown() override;
    IPhysicsFactory* GetFactory() override;
    std::shared_ptr<IPhysicsWorld> GetWorld() override;
    void SetWorld(std::shared_ptr<IPhysicsWorld> world) override;
    RaycastResult Raycast(const Vec3& origin, const Vec3& direction, float maxDistance = 1000.0f) override;
    bool IsInitialized() const override;
    PhysicsEngineType GetEngineType() const override;

private:
    std::unique_ptr<Box2DPhysicsFactory> m_factory;
    std::shared_ptr<IPhysicsWorld> m_world;
    bool m_initialized = false;
};

} // namespace HeavenlyPalace