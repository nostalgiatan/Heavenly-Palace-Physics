// Heavenly Palace Physics - Interface Compilation Test
// SPDX-License-Identifier: MIT

#include "HeavenlyPalacePhysics.h"
#include <iostream>
#include <memory>

using namespace HeavenlyPalace;

/// Simple test to verify that all interfaces compile correctly
int main() {
    std::cout << "Heavenly Palace Physics Interface Test" << std::endl;
    std::cout << "Version: " << GetVersionString() << std::endl;
    
    // Test engine support queries
    uint32_t engineCount;
    const PhysicsEngineType* engines = GetSupportedEngines(engineCount);
    
    std::cout << "Supported engines (" << engineCount << "):" << std::endl;
    for (uint32_t i = 0; i < engineCount; ++i) {
        switch (engines[i]) {
            case PhysicsEngineType::Jolt:
                std::cout << "  - Jolt Physics" << std::endl;
                break;
            case PhysicsEngineType::Bullet:
                std::cout << "  - Bullet Physics" << std::endl;
                break;
            case PhysicsEngineType::PhysX:
                std::cout << "  - NVIDIA PhysX" << std::endl;
                break;
            case PhysicsEngineType::Box2D:
                std::cout << "  - Box2D" << std::endl;
                break;
        }
    }
    
    // Test basic math types
    Vec3 testVec(1.0f, 2.0f, 3.0f);
    std::cout << "Test vector length: " << testVec.Length() << std::endl;
    
    Quaternion testQuat = Quaternion::FromAxisAngle(Vec3(0, 1, 0), 3.14159f / 4);
    Vec3 rotatedVec = testQuat.RotateVector(Vec3(1, 0, 0));
    std::cout << "Rotated vector: (" << rotatedVec.x << ", " << rotatedVec.y << ", " << rotatedVec.z << ")" << std::endl;
    
    // Test AABB
    AABB testBox(Vec3(-1, -1, -1), Vec3(1, 1, 1));
    bool contains = testBox.Contains(Vec3(0.5f, 0.5f, 0.5f));
    std::cout << "AABB contains test point: " << (contains ? "true" : "false") << std::endl;
    
    // Test material properties
    MaterialProperties material(0.5f, 0.3f, 2700.0f); // Aluminum-like
    std::cout << "Material - Friction: " << material.friction << ", Restitution: " << material.restitution << std::endl;
    
    // Test body creation settings
    BodyCreationSettings bodySettings;
    bodySettings.position = Vec3(0, 10, 0);
    bodySettings.mass = 1.0f;
    bodySettings.material = material;
    
    std::cout << "Body settings - Position: (" << bodySettings.position.x << ", " 
              << bodySettings.position.y << ", " << bodySettings.position.z << ")" << std::endl;
    
    // Test engine support check
    bool joltSupported = IsEngineSupported(PhysicsEngineType::Jolt);
    std::cout << "Jolt engine supported: " << (joltSupported ? "true" : "false") << std::endl;
    
    std::cout << "Interface compilation test completed successfully!" << std::endl;
    return 0;
}