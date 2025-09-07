# Heavenly Palace Physics - Universal Physics Engine Abstraction

[![Build Status](https://github.com/nostalgiatan/Heavenly-Palace-Physics/actions/workflows/build.yml/badge.svg)](https://github.com/nostalgiatan/Heavenly-Palace-Physics/actions/)

A universal physics engine abstraction layer that provides a unified interface for multiple physics engines, allowing developers to write physics code once and run it with different physics backends.

## 🌟 Key Features

### Universal Interface
- **Write Once, Run Anywhere:** Same API regardless of underlying physics engine
- **Engine Independence:** Switch between Jolt, Box2D, Bullet, PhysX without code changes
- **Plugin Architecture:** Easy integration of new physics engines through standardized interfaces
- **Performance Flexibility:** Choose optimal engine per platform or use case

### Supported Physics Engines
- ✅ **Jolt Physics** - High-performance 3D physics with advanced features
- ✅ **Box2D** - Battle-tested 2D physics engine
- 🚧 **Bullet Physics** - Comprehensive 3D physics (planned)
- 🚧 **NVIDIA PhysX** - GPU-accelerated physics (planned)

### Engine-Agnostic Features
- Rigid body simulation with multiple motion types
- Comprehensive shape support (box, sphere, capsule, mesh, compound)
- Advanced collision detection and response
- Constraint and joint systems
- Raycast and collision queries
- Material properties and physics materials
- Multi-threaded simulation support

## 🚀 Quick Start

### Installation
```cmake
# Add to your CMakeLists.txt
add_subdirectory(path/to/Heavenly-Palace-Physics/index)
target_link_libraries(your_target PRIVATE HeavenlyPalacePhysics)
```

### Basic Usage
```cpp
#include "HeavenlyPalacePhysics.h"
using namespace HeavenlyPalace;

// Initialize with any supported physics engine
if (!PhysicsManager::CreateSystem(PhysicsEngineType::Jolt)) {
    // Handle initialization error
    return false;
}

// Get factory and create world
auto* system = PhysicsManager::GetInstance();
auto factory = system->GetFactory();
auto world = factory->CreatePhysicsWorld();
world->Initialize(1024, 1024, 1024);
world->SetGravity(Vec3(0, -9.81f, 0));

// Create physics objects
auto boxShape = factory->CreateBoxShape(Vec3(0.5f, 0.5f, 0.5f));
BodyCreationSettings bodySettings;
bodySettings.position = Vec3(0, 10, 0);
bodySettings.mass = 1.0f;
auto body = world->CreateBody(bodySettings);
body->SetShape(boxShape);

// Run simulation
while (running) {
    world->Update(1.0f / 60.0f);
    
    // Get physics results
    Vec3 position = body->GetPosition();
    Quaternion rotation = body->GetRotation();
    
    // Update your game objects...
}

// Cleanup
PhysicsManager::DestroySystem();
```

### Engine Switching
```cpp
// Switch engines at runtime (experimental)
PhysicsManager::SwitchEngine(PhysicsEngineType::Box2D);

// Query available engines
uint32_t count;
const PhysicsEngineType* engines = PhysicsManager::GetAvailableEngines(count);

// Get engine information
const PluginInfo* info = PhysicsManager::GetEngineInfo(PhysicsEngineType::Jolt);
if (info) {
    std::cout << "Engine: " << info->name << " v" << info->version << std::endl;
}
```

## 📖 Documentation

- **[Universal API Documentation](docs/api/)** - Complete abstraction layer reference
- **[Jolt Physics Documentation](docs/jolt/)** - Engine-specific Jolt documentation  
- **[Quick Start Guide](docs/api/quick-start.md)** - Get up and running quickly
- **[Plugin Development Guide](docs/api/plugin-development.md)** - Create your own physics engine plugins

## 🔌 Plugin Architecture

The abstraction layer uses a sophisticated plugin system that allows:

### Automatic Plugin Discovery
```cpp
// Plugins register themselves automatically
REGISTER_PHYSICS_PLUGIN(PhysicsEngineType::MyEngine, MyEnginePlugin);
```

### Runtime Engine Information
```cpp
// Query engine capabilities
const PluginInfo* info = PhysicsManager::GetEngineInfo(engineType);
bool supportsSoftBodies = (info->supportedFeatures & PluginFeature::SoftBodies) != 0;
```

### Custom Engine Integration
```cpp
class MyPhysicsPlugin : public IPhysicsPlugin {
    // Implement plugin interface for your engine
    std::unique_ptr<IPhysicsSystem> CreatePhysicsSystem() override;
    // ... other methods
};
```

## 🏗️ Architecture

### Design Principles
1. **Minimal Overhead** - Thin abstraction layer with minimal performance impact
2. **Type Safety** - Strong typing and clear interfaces throughout
3. **Future Extensibility** - Easy to add new physics engines and features
4. **Engine Compatibility** - Full access to engine-specific features when needed
5. **Plugin Isolation** - Engines are isolated and can be loaded/unloaded independently

### Core Interfaces
- **`IPhysicsSystem`** - Main entry point for physics operations
- **`IPhysicsWorld`** - Physics simulation world/context
- **`IPhysicsBody`** - Rigid body representation
- **`IShape`** - Collision shape interfaces (Box, Sphere, Capsule, Mesh, Compound)
- **`IPhysicsFactory`** - Factory for creating physics objects
- **`IPhysicsPlugin`** - Plugin interface for physics engines

## 🎯 Use Cases

### Game Development
- **Multi-platform games** requiring different physics engines per platform
- **Performance optimization** through engine selection
- **Rapid prototyping** with engine-agnostic physics code

### Simulation & VR
- **Scientific simulations** with pluggable physics backends
- **VR applications** requiring deterministic or high-precision physics
- **Educational tools** comparing different physics engine behaviors

### Research & Development
- **Physics engine comparison** and benchmarking
- **Algorithm development** with multiple backend validation
- **Performance analysis** across different physics implementations

## 🛠️ Building

### Requirements
- C++17 compatible compiler
- CMake 3.20 or later
- Git (for submodules)

### Build Instructions
```bash
git clone --recursive https://github.com/nostalgiatan/Heavenly-Palace-Physics.git
cd Heavenly-Palace-Physics
mkdir build && cd build
cmake ../Build
make -j$(nproc)
```

### Running Tests
```bash
# Basic interface tests
./HeavenlyPalacePhysicsTest

# Engine-specific tests
ctest --verbose

# Performance benchmarks
make benchmark-check-all
```

## 🤝 Contributing

We welcome contributions! Whether you're:
- Adding support for new physics engines
- Improving the abstraction layer interfaces
- Writing documentation and examples
- Fixing bugs or optimizing performance

### Development Workflow
1. **Fork the repository**
2. **Create feature branch** (`git checkout -b feature/amazing-feature`)
3. **Make your changes** following our coding standards
4. **Add tests** for new functionality
5. **Update documentation** as needed
6. **Submit pull request**

### Adding New Physics Engines
1. Implement the `IPhysicsPlugin` interface
2. Create engine-specific implementations of core interfaces
3. Register your plugin using `REGISTER_PHYSICS_PLUGIN`
4. Add tests and documentation
5. Update the supported engines list

## 📊 Performance

The abstraction layer is designed for minimal overhead:
- **Virtual call overhead:** ~1-3ns per call on modern CPUs
- **Memory overhead:** <1% additional memory usage
- **Feature parity:** Full access to engine-specific optimizations

Performance benchmarks and comparisons available in the [docs/jolt/PerformanceTest.md](docs/jolt/PerformanceTest.md).

## 📜 License

This project is distributed under the [MIT License](LICENSE).

## 🙏 Acknowledgments

- **[Jolt Physics](https://github.com/jrouwe/JoltPhysics)** by Jorrit Rouwe - Primary 3D physics backend
- **[Box2D](https://github.com/erincatto/box2d)** by Erin Catto - 2D physics backend
- **Physics Engine Communities** - For inspiration and technical guidance

---

**Heavenly Palace Physics** - Unifying the physics simulation ecosystem, one interface at a time. 🌌