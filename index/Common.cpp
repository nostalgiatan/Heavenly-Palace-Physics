// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT

#include "Common.h"
#include <cmath>

namespace HeavenlyPalace {

// Vec3 implementation
float Vec3::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vec3::LengthSquared() const {
    return x * x + y * y + z * z;
}

Vec3 Vec3::Normalized() const {
    float len = Length();
    if (len < 1e-6f) return Vec3(0, 0, 0);
    return Vec3(x / len, y / len, z / len);
}

// Quaternion implementation
Quaternion Quaternion::FromAxisAngle(const Vec3& axis, float angle) {
    float halfAngle = angle * 0.5f;
    float s = std::sin(halfAngle);
    Vec3 normalizedAxis = axis.Normalized();
    return Quaternion(
        normalizedAxis.x * s,
        normalizedAxis.y * s,
        normalizedAxis.z * s,
        std::cos(halfAngle)
    );
}

Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll) {
    float cp = std::cos(pitch * 0.5f);
    float sp = std::sin(pitch * 0.5f);
    float cy = std::cos(yaw * 0.5f);
    float sy = std::sin(yaw * 0.5f);
    float cr = std::cos(roll * 0.5f);
    float sr = std::sin(roll * 0.5f);

    return Quaternion(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy
    );
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Vec3 Quaternion::RotateVector(const Vec3& vector) const {
    // q * v * q^-1
    Vec3 qv(x, y, z);
    Vec3 uv = Vec3(
        qv.y * vector.z - qv.z * vector.y,
        qv.z * vector.x - qv.x * vector.z,
        qv.x * vector.y - qv.y * vector.x
    );
    Vec3 uuv = Vec3(
        qv.y * uv.z - qv.z * uv.y,
        qv.z * uv.x - qv.x * uv.z,
        qv.x * uv.y - qv.y * uv.x
    );
    
    return vector + (uv * w + uuv) * 2.0f;
}

Quaternion Quaternion::Normalized() const {
    float len = std::sqrt(x * x + y * y + z * z + w * w);
    if (len < 1e-6f) return Identity();
    return Quaternion(x / len, y / len, z / len, w / len);
}

// AABB implementation
bool AABB::Contains(const Vec3& point) const {
    return point.x >= min.x && point.x <= max.x &&
           point.y >= min.y && point.y <= max.y &&
           point.z >= min.z && point.z <= max.z;
}

bool AABB::Intersects(const AABB& other) const {
    return max.x >= other.min.x && min.x <= other.max.x &&
           max.y >= other.min.y && min.y <= other.max.y &&
           max.z >= other.min.z && min.z <= other.max.z;
}

} // namespace HeavenlyPalace