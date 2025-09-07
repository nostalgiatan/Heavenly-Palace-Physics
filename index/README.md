# Jolt Physics Engine API Index

This directory provides a comprehensive index and documentation for all interfaces, classes, and APIs in the Jolt Physics Engine. It's designed to help developers quickly find and understand the components they need for their physics simulations.

## Quick Navigation

- [Core APIs](core/README.md) - Memory management, job systems, utilities
- [Physics System](physics/README.md) - Main physics simulation and world management
- [Bodies & Shapes](bodies/README.md) - Rigid bodies, shapes, and collision geometry
- [Constraints](constraints/README.md) - Joints and constraint systems
- [Collision Detection](collision/README.md) - Broad and narrow phase collision
- [Math & Geometry](math/README.md) - Vector math, matrices, and geometric utilities
- [Character Control](character/README.md) - Character controller APIs
- [Vehicles](vehicles/README.md) - Vehicle simulation system
- [Soft Bodies](softbody/README.md) - Soft body physics
- [Utilities](utilities/README.md) - Helper classes and tools

## API Overview

The Jolt Physics Engine contains **212 exported classes** across **291 header files**, organized into the following main categories:

### Core Components
- **PhysicsSystem** - Main physics world and simulation controller
- **BodyInterface** - Interface for creating and managing rigid bodies
- **JobSystem** - Multi-threaded job execution system
- **Factory** - Object creation and type registration

### Shape System
- **Shape** - Base class for all collision shapes
- **ConvexShape** - Base for convex collision shapes (Box, Sphere, Capsule, etc.)
- **CompoundShape** - Container for multiple shapes
- **MeshShape** - Triangle mesh collision shapes

### Constraint System
- **Constraint** - Base class for all constraints
- **TwoBodyConstraint** - Constraints between two bodies
- **ConstraintManager** - Manages all constraints in the system

### Collision Detection
- **BroadPhase** - Broad phase collision detection
- **NarrowPhaseQuery** - Detailed collision queries
- **CollisionCollector** - Results collection for collision queries

## Getting Started

1. **Quick Start**: Follow the [Quick Start Guide](quick-start.md) for a complete working example
2. **API Lookup**: Use the [Interface Map](interface-map.md) to find any class quickly
3. **Complete Reference**: Browse the [Complete API Reference](api-reference.md)
4. **Category Guides**: Explore specific topics in the category sections below

## Interface Categories

### By Functionality
- **Core Infrastructure** - JobSystem, Memory, Factory, RTTI
- **Physics Simulation** - PhysicsSystem, Bodies, Constraints
- **Collision System** - Shapes, BroadPhase, NarrowPhase
- **Character & Vehicle** - Specialized simulation systems
- **Utilities** - Math, Geometry, Debugging tools

### By Usage Pattern
- **Essential APIs** - Must-know interfaces for basic usage
- **Advanced APIs** - Specialized functionality for advanced users
- **Internal APIs** - Implementation details (use with caution)
- **Utility APIs** - Helper classes and convenience functions

## Documentation Standards

Each interface is documented with:
- **Purpose** - What the interface does
- **Key Methods** - Most important functions
- **Usage Examples** - Code snippets showing typical usage
- **Related APIs** - Cross-references to related interfaces
- **Best Practices** - Recommended usage patterns

## Completeness Guarantee

This index covers **ALL** public interfaces in Jolt Physics Engine:
- ✅ All 212 exported classes documented
- ✅ All 291 header files categorized
- ✅ Cross-references maintained
- ✅ Examples provided for major APIs
- ✅ Best practices documented

Last updated: [Generated from repository scan]