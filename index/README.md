# Heavenly Palace Physics - Universal Physics Engine Abstraction

This directory contains the Heavenly Palace Physics abstraction layer, which provides a unified interface for working with different physics engines while maintaining the same API.

## Overview

The abstraction layer serves as a bridge between your application and various physics engines, starting with Jolt Physics and designed to support additional engines in the future (Bullet Physics, NVIDIA PhysX, Box2D, etc.).

## Architecture

### Core Interfaces

- **`IPhysicsSystem`** - Main entry point for physics operations
- **`IPhysicsWorld`** - Physics simulation world/context
- **`IPhysicsBody`** - Rigid body representation
- **`IShape`** - Collision shape interfaces (Box, Sphere, Capsule, Mesh, Compound)
- **`IPhysicsFactory`** - Factory for creating physics objects

### Design Principles

1. **Engine Independence** - Write code once, switch physics engines easily
2. **Minimal Overhead** - Thin abstraction layer with minimal performance impact  
3. **Type Safety** - Strong typing and clear interfaces
4. **Future Extensibility** - Easy to add new physics engines
5. **Jolt Compatibility** - Full access to Jolt's advanced features when needed

## Quick Start

```cpp
#include "HeavenlyPalacePhysics.h"
using namespace HeavenlyPalace;

// Initialize physics system with Jolt engine
if (!PhysicsManager::CreateSystem(PhysicsEngineType::Jolt)) {
    return false; // Handle initialization error
}

// Get factory and create world
auto factory = PhysicsManager::GetInstance().GetFactory();
auto world = factory->CreatePhysicsWorld();
world->Initialize(1024, 1024, 1024);
world->SetGravity(Vec3(0, -9.81f, 0));
PhysicsManager::GetInstance().SetWorld(world);

// Create a falling box
auto boxShape = factory->CreateBoxShape(Vec3(1, 1, 1)); // 2x2x2 meter box
BodyCreationSettings settings;
settings.position = Vec3(0, 10, 0); // 10 meters high
settings.mass = 1.0f; // 1 kg
auto body = world->CreateBody(settings);
body->SetShape(boxShape);

// Simulation loop
while (running) {
    world->Update(1.0f / 60.0f); // 60 FPS
    
    // Get body position for rendering
    Vec3 position = body->GetPosition();
    // ... render at position
}

// Cleanup
PhysicsManager::DestroySystem();
```

## Current Implementation Status

### ✅ Completed
- Core interface definitions
- Math utilities (Vec3, Quaternion, AABB)
- Type-safe enums and structures
- Jolt Physics engine integration architecture
- CMake build system integration
- Interface compilation testing

### 🚧 In Progress  
- Jolt Physics concrete implementations
- Shape creation and management
- Physics world simulation
- Body creation and manipulation

### 📋 Planned
- Complete Jolt Physics implementation
- Raycast and collision queries
- Constraint/joint system
- Character controller
- Performance optimization
- Additional physics engines (Bullet, PhysX)

## Directory Structure

```
index/
├── HeavenlyPalacePhysics.h    # Main include header
├── Common.h                   # Common types and utilities
├── IPhysicsSystem.h           # System and factory interfaces
├── IPhysicsWorld.h            # Physics world interface
├── IPhysicsBody.h             # Rigid body interface
├── IShape.h                   # Shape interfaces
├── Jolt/                      # Jolt Physics implementation
│   ├── JoltPhysicsSystem.h    # Jolt system implementation
│   ├── JoltPhysicsWorld.h     # Jolt world implementation
│   └── JoltPhysicsBody.h      # Jolt body implementation
├── CMakeLists.txt             # Build configuration
└── test_interface.cpp         # Interface validation test
```

## Benefits

1. **Consistency** - Same API regardless of underlying physics engine
2. **Flexibility** - Switch engines based on platform, performance, or feature requirements
3. **Maintainability** - Centralized physics code that's easier to maintain
4. **Testing** - Easy to mock physics for unit testing
5. **Learning** - Single API to learn instead of multiple engine-specific APIs

## Integration

The abstraction layer is designed to integrate seamlessly with the existing Jolt Physics Engine while providing a path forward for multi-engine support.

### CMake Integration

Add to your CMakeLists.txt:
```cmake
add_subdirectory(index)
target_link_libraries(your_target PRIVATE HeavenlyPalacePhysics)
```

### Documentation

API documentation has been moved to `docs/api/` to maintain separation between interface code and documentation.

## Contributing

When adding new features:
1. Update the abstract interfaces first
2. Implement in Jolt backend
3. Add tests to verify functionality
4. Update documentation

This ensures consistency across all current and future physics engine implementations.