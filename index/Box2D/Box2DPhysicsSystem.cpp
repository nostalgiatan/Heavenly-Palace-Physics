// Heavenly Palace Physics - Box2D Physics Engine Implementation
// SPDX-License-Identifier: MIT

#include "Box2DPhysicsSystem.h"
#include "Box2DPhysicsWorld.h"
#include "../Common.h"
#include <stdexcept>

namespace HeavenlyPalace {

//==============================================================================
// Box2DPhysicsFactory Implementation
//==============================================================================

Box2DPhysicsFactory::Box2DPhysicsFactory() = default;

Box2DPhysicsFactory::~Box2DPhysicsFactory() = default;

std::shared_ptr<IPhysicsWorld> Box2DPhysicsFactory::CreatePhysicsWorld() {
    auto world = std::make_shared<Box2DPhysicsWorld>();
    if (!world->Initialize(1024, 4096, 2048)) { // Default values for Box2D
        return nullptr;
    }
    return world;
}

std::shared_ptr<IBoxShape> Box2DPhysicsFactory::CreateBoxShape(const Vec3& halfExtents) {
    // Note: Box2D is 2D, so we ignore the Z component
    // For now, return nullptr as we need to implement Box2D-specific shapes
    return nullptr;
}

std::shared_ptr<ISphereShape> Box2DPhysicsFactory::CreateSphereShape(float radius) {
    // Note: Box2D uses circles instead of spheres
    // For now, return nullptr as we need to implement Box2D-specific shapes
    return nullptr;
}

std::shared_ptr<ICapsuleShape> Box2DPhysicsFactory::CreateCapsuleShape(float radius, float height) {
    // Note: Box2D doesn't have native capsule shapes
    // For now, return nullptr as we need to implement Box2D-specific shapes
    return nullptr;
}

std::shared_ptr<IMeshShape> Box2DPhysicsFactory::CreateMeshShape(const Vec3* vertices, uint32_t vertexCount,
                                                                const uint32_t* indices, uint32_t indexCount) {
    // Note: Box2D uses polygons instead of 3D meshes
    // For now, return nullptr as we need to implement Box2D-specific shapes
    return nullptr;
}

std::shared_ptr<ICompoundShape> Box2DPhysicsFactory::CreateCompoundShape() {
    // Note: Box2D handles compound shapes differently
    // For now, return nullptr as we need to implement Box2D-specific shapes
    return nullptr;
}

//==============================================================================
// Box2DPhysicsSystem Implementation
//==============================================================================

Box2DPhysicsSystem::Box2DPhysicsSystem() = default;

Box2DPhysicsSystem::~Box2DPhysicsSystem() {
    Shutdown();
}

bool Box2DPhysicsSystem::Initialize(PhysicsEngineType engineType) {
    if (m_initialized) {
        return true;
    }

    if (engineType != PhysicsEngineType::Box2D) {
        return false;
    }

    try {
        m_factory = std::make_unique<Box2DPhysicsFactory>();
        m_initialized = true;
        return true;
    } catch (const std::exception&) {
        m_factory.reset();
        m_initialized = false;
        return false;
    }
}

void Box2DPhysicsSystem::Shutdown() {
    if (!m_initialized) {
        return;
    }

    m_world.reset();
    m_factory.reset();
    m_initialized = false;
}

IPhysicsFactory* Box2DPhysicsSystem::GetFactory() {
    return m_factory.get();
}

std::shared_ptr<IPhysicsWorld> Box2DPhysicsSystem::GetWorld() {
    return m_world;
}

void Box2DPhysicsSystem::SetWorld(std::shared_ptr<IPhysicsWorld> world) {
    m_world = world;
}

RaycastResult Box2DPhysicsSystem::Raycast(const Vec3& origin, const Vec3& direction, float maxDistance) {
    if (!m_world) {
        return RaycastResult{}; // Return empty result
    }
    
    // Cast to Box2D world to access the Raycast method
    auto box2dWorld = std::dynamic_pointer_cast<Box2DPhysicsWorld>(m_world);
    if (box2dWorld) {
        return box2dWorld->Raycast(origin, direction, maxDistance);
    }
    
    return RaycastResult{}; // Return empty result if cast fails
}

bool Box2DPhysicsSystem::IsInitialized() const {
    return m_initialized;
}

PhysicsEngineType Box2DPhysicsSystem::GetEngineType() const {
    return PhysicsEngineType::Box2D;
}

} // namespace HeavenlyPalace