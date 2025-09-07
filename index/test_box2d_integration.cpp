// Heavenly Palace Physics - Box2D Integration Test
// SPDX-License-Identifier: MIT

#include "Box2D/Box2DPhysicsSystem.h"
#include "HeavenlyPalacePhysics.h"
#include <iostream>
#include <cassert>

using namespace HeavenlyPalace;

int main() {
    std::cout << "Testing Box2D Integration for Heavenly Palace Physics " 
              << GetVersionString() << std::endl;

    // Test 1: Check if Box2D is listed as a supported engine
    std::cout << "\n1. Checking supported engines..." << std::endl;
    uint32_t engineCount = 0;
    const PhysicsEngineType* engines = GetSupportedEngines(engineCount);
    
    bool box2dSupported = false;
    for (uint32_t i = 0; i < engineCount; ++i) {
        if (engines[i] == PhysicsEngineType::Box2D) {
            box2dSupported = true;
            break;
        }
    }
    
    if (box2dSupported) {
        std::cout << "   ✓ Box2D is listed as supported engine" << std::endl;
    } else {
        std::cout << "   ✗ Box2D is NOT listed as supported engine" << std::endl;
        return 1;
    }

    // Test 2: Check IsEngineSupported function
    std::cout << "\n2. Testing IsEngineSupported function..." << std::endl;
    if (IsEngineSupported(PhysicsEngineType::Box2D)) {
        std::cout << "   ✓ IsEngineSupported(Box2D) returns true" << std::endl;
    } else {
        std::cout << "   ✗ IsEngineSupported(Box2D) returns false" << std::endl;
        return 1;
    }

    // Test 3: Create Box2D physics system
    std::cout << "\n3. Creating Box2D physics system..." << std::endl;
    Box2DPhysicsSystem box2dSystem;
    
    if (box2dSystem.Initialize(PhysicsEngineType::Box2D)) {
        std::cout << "   ✓ Box2D physics system initialized successfully" << std::endl;
    } else {
        std::cout << "   ✗ Failed to initialize Box2D physics system" << std::endl;
        return 1;
    }

    // Test 4: Check system properties
    std::cout << "\n4. Testing system properties..." << std::endl;
    
    if (box2dSystem.IsInitialized()) {
        std::cout << "   ✓ System reports as initialized" << std::endl;
    } else {
        std::cout << "   ✗ System does not report as initialized" << std::endl;
        return 1;
    }
    
    if (box2dSystem.GetEngineType() == PhysicsEngineType::Box2D) {
        std::cout << "   ✓ System reports correct engine type" << std::endl;
    } else {
        std::cout << "   ✗ System reports incorrect engine type" << std::endl;
        return 1;
    }

    // Test 5: Get factory
    std::cout << "\n5. Testing factory access..." << std::endl;
    auto* factory = box2dSystem.GetFactory();
    if (factory != nullptr) {
        std::cout << "   ✓ Factory is accessible" << std::endl;
        
        if (factory->GetEngineType() == PhysicsEngineType::Box2D) {
            std::cout << "   ✓ Factory reports correct engine type" << std::endl;
        } else {
            std::cout << "   ✗ Factory reports incorrect engine type" << std::endl;
            return 1;
        }
    } else {
        std::cout << "   ✗ Factory is null" << std::endl;
        return 1;
    }

    // Test 6: Create physics world (basic test)
    std::cout << "\n6. Testing world creation..." << std::endl;
    auto world = factory->CreatePhysicsWorld();
    if (world != nullptr) {
        std::cout << "   ✓ Physics world created successfully" << std::endl;
        
        // Test gravity setting/getting
        Vec3 testGravity(0.0f, -10.0f, 0.0f);
        world->SetGravity(testGravity);
        Vec3 retrievedGravity = world->GetGravity();
        if (retrievedGravity.y == testGravity.y) {
            std::cout << "   ✓ Gravity setting/getting works" << std::endl;
        } else {
            std::cout << "   ✗ Gravity setting/getting failed" << std::endl;
            return 1;
        }
    } else {
        std::cout << "   ✗ Failed to create physics world" << std::endl;
        return 1;
    }

    // Test 7: Shutdown
    std::cout << "\n7. Testing shutdown..." << std::endl;
    box2dSystem.Shutdown();
    
    if (!box2dSystem.IsInitialized()) {
        std::cout << "   ✓ System shutdown successfully" << std::endl;
    } else {
        std::cout << "   ✗ System did not shutdown properly" << std::endl;
        return 1;
    }

    std::cout << "\n✓ All Box2D integration tests passed!" << std::endl;
    return 0;
}