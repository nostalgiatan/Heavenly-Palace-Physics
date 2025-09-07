# Jolt Physics Engine Documentation

This directory contains comprehensive documentation for the Jolt Physics Engine, which serves as the primary backend implementation for the Heavenly Palace Physics abstraction layer.

## Documentation Contents

### Core Documentation
- **`Architecture.md`** - Detailed architecture and implementation details of Jolt Physics
- **`APIChanges.md`** - API changes and migration guides between Jolt versions
- **`ReleaseNotes.md`** - Version history and release notes for Jolt Physics

### Development & Testing
- **`CI-Testing-Guide.md`** - Comprehensive CI/CD system and testing configuration
- **`PerformanceTest.md`** - Performance testing and benchmarking documentation
- **`Samples.md`** - Documentation for Jolt sample applications

### Project Information
- **`ProjectsUsingJolt.md`** - List of projects and games using Jolt Physics

### Visual Resources
- **`Images/`** - Technical diagrams, charts, and visual documentation
- **`PhysicsSystemUpdate.drawio`** - Editable physics system diagrams
- **`PhysicsSystemUpdate.svg`** - Physics system flow diagrams
- **`SwingTwistConstraint.png`** - Constraint system visualizations

## About Jolt Physics

Jolt Physics is a multi-core friendly rigid body physics and collision detection library suitable for games and VR applications. It's used by major titles including Horizon Forbidden West and Death Stranding 2: On the Beach.

### Key Features
- High-performance multi-threaded simulation
- Deterministic cross-platform behavior
- Comprehensive shape types (sphere, box, capsule, convex hull, mesh, etc.)
- Advanced constraint system
- Soft body simulation
- Character controllers
- Vehicle simulation

## Integration with Heavenly Palace Physics

While this documentation covers Jolt-specific implementation details, the Heavenly Palace Physics abstraction layer provides:

- **Universal Interface:** Same API for Jolt and other physics engines
- **Engine Independence:** Switch between physics engines without code changes
- **Plugin Architecture:** Easy integration of additional physics engines
- **Performance Flexibility:** Choose optimal engine per platform/use case

## Using This Documentation

1. **For Jolt-Specific Features:** Use this documentation to understand Jolt's unique capabilities
2. **For Architecture Understanding:** Reference `Architecture.md` for deep implementation details
3. **For Performance Optimization:** See `PerformanceTest.md` for benchmarking approaches
4. **For Integration:** Combine with `../api/` documentation for abstraction layer usage

## Migration Path

**Existing Jolt Code:**
- Continue working without changes
- Gradually migrate to abstraction layer for portability
- Use Jolt-specific features when needed through engine-specific interfaces

**New Development:**
- Start with universal abstraction layer (`../api/` documentation)
- Fall back to Jolt-specific features when universal interface is insufficient
- Contribute missing features to abstraction layer for future portability

This documentation serves both as reference for direct Jolt usage and as implementation guide for the abstraction layer's Jolt backend.