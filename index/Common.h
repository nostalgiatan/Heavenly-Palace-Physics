// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>
#include <string>

namespace HeavenlyPalace {

/// 3D Vector
struct Vec3 {
    float x, y, z;
    
    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    
    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    
    float Length() const;
    float LengthSquared() const;
    Vec3 Normalized() const;
};

/// Quaternion for rotations
struct Quaternion {
    float x, y, z, w;
    
    Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
    
    static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }
    static Quaternion FromAxisAngle(const Vec3& axis, float angle);
    static Quaternion FromEuler(float pitch, float yaw, float roll);
    
    Quaternion operator*(const Quaternion& other) const;
    Vec3 RotateVector(const Vec3& vector) const;
    Quaternion Normalized() const;
};

/// Axis-aligned bounding box
struct AABB {
    Vec3 min, max;
    
    AABB() : min(0, 0, 0), max(0, 0, 0) {}
    AABB(const Vec3& min, const Vec3& max) : min(min), max(max) {}
    
    Vec3 GetCenter() const { return (min + max) * 0.5f; }
    Vec3 GetSize() const { return max - min; }
    bool Contains(const Vec3& point) const;
    bool Intersects(const AABB& other) const;
};

/// Material properties for physics objects
struct MaterialProperties {
    float friction = 0.2f;        ///< Friction coefficient
    float restitution = 0.0f;     ///< Bounciness (0 = no bounce, 1 = perfect bounce)
    float density = 1000.0f;      ///< Density in kg/m³
    
    MaterialProperties() = default;
    MaterialProperties(float friction, float restitution, float density = 1000.0f)
        : friction(friction), restitution(restitution), density(density) {}
};

/// Settings for creating a physics body
struct BodyCreationSettings {
    Vec3 position = Vec3(0, 0, 0);           ///< Initial position
    Quaternion rotation = Quaternion::Identity(); ///< Initial rotation
    Vec3 linearVelocity = Vec3(0, 0, 0);     ///< Initial linear velocity
    Vec3 angularVelocity = Vec3(0, 0, 0);    ///< Initial angular velocity
    MaterialProperties material;              ///< Material properties
    float mass = 1.0f;                       ///< Mass in kg (0 for infinite mass)
    bool isSensor = false;                   ///< True if this is a sensor (no collision response)
    uint32_t collisionGroup = 0;             ///< Collision group for filtering
    uint32_t collisionMask = 0xFFFFFFFF;     ///< Collision mask for filtering
};

/// Result of a raycast query
struct RaycastResult {
    bool hasHit = false;        ///< True if ray hit something
    Vec3 hitPoint;              ///< World space hit point
    Vec3 hitNormal;             ///< Surface normal at hit point
    float distance = 0.0f;      ///< Distance from ray origin to hit point
    uint32_t bodyId = 0;        ///< ID of the body that was hit
};

/// Physics engine types
enum class PhysicsEngineType {
    Jolt,       ///< Jolt Physics Engine
    Bullet,     ///< Bullet Physics (future)
    PhysX,      ///< NVIDIA PhysX (future)
    Box2D       ///< Box2D for 2D physics (future)
};

/// Plugin feature flags
enum class PluginFeature : uint32_t {
    SoftBodies         = 1 << 0,  ///< Soft body simulation
    FluidSimulation    = 1 << 1,  ///< Fluid/particle simulation  
    CharacterControl   = 1 << 2,  ///< Character controller
    VehicleSimulation  = 1 << 3,  ///< Vehicle physics
    ClothSimulation    = 1 << 4,  ///< Cloth simulation
    DestructibleBodies = 1 << 5,  ///< Destructible objects
    ContinuousCD       = 1 << 6,  ///< Continuous collision detection
    Deterministic      = 1 << 7,  ///< Deterministic simulation
    DoublePrecision    = 1 << 8,  ///< Double precision math
    Multithreading     = 1 << 9,  ///< Multi-threaded simulation
    GPU_Acceleration   = 1 << 10, ///< GPU acceleration
    PBD_Solver         = 1 << 11  ///< Position-based dynamics solver
};

/// Plugin information structure
struct PluginInfo {
    std::string name;               ///< Human-readable name of the plugin
    std::string version;            ///< Plugin version string
    std::string description;        ///< Brief description of the plugin
    PhysicsEngineType engineType;  ///< Engine type this plugin provides
    std::string author;             ///< Plugin author/organization
    uint32_t apiVersion = 1;        ///< API version this plugin was built for
    bool isSupported = true;        ///< Whether this plugin is supported on current platform
    uint32_t supportedFeatures = 0; ///< Bitmask of supported features
};

} // namespace HeavenlyPalace