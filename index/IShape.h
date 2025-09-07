// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <memory>

namespace HeavenlyPalace {

/// Shape types supported by the physics engine
enum class ShapeType {
    Box,        ///< Box/cube shape
    Sphere,     ///< Sphere shape
    Capsule,    ///< Capsule shape
    Cylinder,   ///< Cylinder shape
    Cone,       ///< Cone shape
    Plane,      ///< Infinite plane
    Mesh,       ///< Triangle mesh
    Compound    ///< Compound shape (collection of other shapes)
};

/// Abstract interface for collision shapes
class IShape {
public:
    virtual ~IShape() = default;

    /// Get the type of this shape
    /// @return Shape type
    virtual ShapeType GetType() const = 0;

    /// Get the local bounding box of this shape
    /// @return Axis-aligned bounding box in local space
    virtual AABB GetLocalBounds() const = 0;

    /// Calculate the mass properties for this shape
    /// @param density Material density in kg/m³
    /// @return Mass in kg (0 for infinite mass)
    virtual float CalculateMass(float density) const = 0;

    /// Get the volume of this shape
    /// @return Volume in m³
    virtual float GetVolume() const = 0;

    /// Get the surface area of this shape
    /// @return Surface area in m²
    virtual float GetSurfaceArea() const = 0;

    /// Check if a point is inside this shape (local space)
    /// @param point Point to test in local coordinates
    /// @return True if point is inside the shape
    virtual bool ContainsPoint(const Vec3& point) const = 0;

    /// Get the center of mass in local space
    /// @return Center of mass position
    virtual Vec3 GetCenterOfMass() const = 0;

    /// Create a copy of this shape
    /// @return New instance of the same shape
    virtual std::shared_ptr<IShape> Clone() const = 0;
};

/// Interface for box shapes
class IBoxShape : public IShape {
public:
    virtual ~IBoxShape() = default;
    ShapeType GetType() const override { return ShapeType::Box; }

    /// Get the half extents of the box (half width, half height, half depth)
    /// @return Half extents vector
    virtual Vec3 GetHalfExtents() const = 0;

    /// Set the half extents of the box
    /// @param halfExtents New half extents
    virtual void SetHalfExtents(const Vec3& halfExtents) = 0;
};

/// Interface for sphere shapes
class ISphereShape : public IShape {
public:
    virtual ~ISphereShape() = default;
    ShapeType GetType() const override { return ShapeType::Sphere; }

    /// Get the radius of the sphere
    /// @return Radius in meters
    virtual float GetRadius() const = 0;

    /// Set the radius of the sphere
    /// @param radius New radius in meters
    virtual void SetRadius(float radius) = 0;
};

/// Interface for capsule shapes (cylinder with spherical caps)
class ICapsuleShape : public IShape {
public:
    virtual ~ICapsuleShape() = default;
    ShapeType GetType() const override { return ShapeType::Capsule; }

    /// Get the radius of the capsule
    /// @return Radius in meters
    virtual float GetRadius() const = 0;

    /// Get the height of the cylindrical part (excluding caps)
    /// @return Height in meters
    virtual float GetHeight() const = 0;

    /// Set the radius of the capsule
    /// @param radius New radius in meters
    virtual void SetRadius(float radius) = 0;

    /// Set the height of the cylindrical part
    /// @param height New height in meters
    virtual void SetHeight(float height) = 0;
};

/// Interface for mesh shapes (triangle mesh)
class IMeshShape : public IShape {
public:
    virtual ~IMeshShape() = default;
    ShapeType GetType() const override { return ShapeType::Mesh; }

    /// Get the number of vertices in the mesh
    /// @return Vertex count
    virtual uint32_t GetVertexCount() const = 0;

    /// Get the number of triangles in the mesh
    /// @return Triangle count
    virtual uint32_t GetTriangleCount() const = 0;

    /// Get vertex data
    /// @param vertices Output array of vertices (must be pre-allocated)
    virtual void GetVertices(Vec3* vertices) const = 0;

    /// Get triangle indices
    /// @param indices Output array of indices (must be pre-allocated, size = triangleCount * 3)
    virtual void GetIndices(uint32_t* indices) const = 0;
};

/// Interface for compound shapes (collection of other shapes)
class ICompoundShape : public IShape {
public:
    virtual ~ICompoundShape() = default;
    ShapeType GetType() const override { return ShapeType::Compound; }

    /// Add a child shape with relative transform
    /// @param shape Child shape to add
    /// @param position Position relative to compound center
    /// @param rotation Rotation relative to compound orientation
    virtual void AddShape(std::shared_ptr<IShape> shape, const Vec3& position = Vec3(0,0,0), 
                         const Quaternion& rotation = Quaternion::Identity()) = 0;

    /// Remove a child shape
    /// @param index Index of shape to remove
    virtual void RemoveShape(uint32_t index) = 0;

    /// Get the number of child shapes
    /// @return Number of child shapes
    virtual uint32_t GetShapeCount() const = 0;

    /// Get a child shape
    /// @param index Index of the child shape
    /// @return Child shape or nullptr if index is invalid
    virtual std::shared_ptr<IShape> GetShape(uint32_t index) const = 0;

    /// Get the transform of a child shape
    /// @param index Index of the child shape
    /// @param position Output position relative to compound center
    /// @param rotation Output rotation relative to compound orientation
    virtual void GetShapeTransform(uint32_t index, Vec3& position, Quaternion& rotation) const = 0;
};

} // namespace HeavenlyPalace