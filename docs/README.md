# Heavenly Palace Physics Documentation

This directory contains comprehensive documentation for the Heavenly Palace Physics project and its universal physics engine abstraction layer.

## Directory Structure

### `api/` - Universal Physics Abstraction API Documentation
This directory contains documentation for the universal physics engine abstraction layer that provides a unified interface across multiple physics engines.

**Contents:**
- `README.md` - Main API overview and navigation
- `quick-start.md` - Complete getting started example  
- `api-reference.md` - All abstraction layer classes by category
- `interface-map.md` - Quick lookup and search
- `navigation.md` - Documentation navigation guide
- `bodies/` - Bodies & shapes documentation
- `constraints/` - Constraints documentation
- `core/` - Core infrastructure documentation
- `physics/` - Physics system documentation

### `jolt/` - Jolt Physics Engine Documentation
This directory contains Jolt-specific documentation that was consolidated from the previous `Docs/` directory.

**Contents:**
- `APIChanges.md` - Jolt API changes and migration guides
- `Architecture.md` - Jolt physics engine architecture details
- `ReleaseNotes.md` - Jolt release notes and version history
- `Samples.md` - Jolt sample applications documentation
- `PerformanceTest.md` - Performance testing documentation
- `ProjectsUsingJolt.md` - List of projects using Jolt Physics
- `CI-Testing-Guide.md` - CI/CD and testing configuration
- `Images/` - Diagrams and visual documentation
- Various technical diagrams and reference materials

## Project Philosophy

**Universal Physics Engine Abstraction:** The Heavenly Palace Physics project provides a unified interface for multiple physics engines, allowing developers to:

1. **Write Once, Run Anywhere:** Same API regardless of underlying physics engine
2. **Engine Flexibility:** Switch between Jolt, Bullet, PhysX, Box2D based on requirements
3. **Plugin System:** Easy integration of new physics engines through standardized interfaces
4. **Performance Optimization:** Choose the best engine for specific platforms or use cases

## Key Changes from Original Structure

1. **Documentation Consolidated:** All documentation now under single `docs/` directory
2. **Engine-Specific Docs:** Jolt documentation moved to `docs/jolt/` subdirectory
3. **Abstraction Focus:** Main documentation focuses on universal interface rather than specific engines
4. **Clean Organization:** Removed duplicate directories and large unnecessary assets
5. **Plugin Architecture:** Enhanced support for multiple physics engine backends

## Using the Documentation

- **For Universal API:** Start with `api/` directory for abstraction layer documentation
- **For Jolt-Specific Features:** See `jolt/` directory for engine-specific documentation
- **For Implementation:** See `../index/README.md` for the abstraction layer code structure
- **For Getting Started:** Begin with `api/quick-start.md` for universal interface examples

## Migration Guide

**From Direct Jolt Usage:**
- Existing code using Jolt directly remains unchanged
- New code can use the abstraction layer for portability
- Gradual migration path available through compatibility interfaces

**For Plugin Developers:**
- Implement the abstract interfaces in `../index/` directory
- Follow the patterns established by existing Jolt and Box2D implementations
- Refer to `api/` documentation for interface specifications

This restructured documentation supports the project's evolution from a Jolt-specific wrapper to a truly universal physics engine abstraction layer.