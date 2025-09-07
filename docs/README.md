# Heavenly Palace Physics Documentation

This directory contains documentation for the Heavenly Palace Physics project.

## Directory Structure

### `api/` - Physics Engine API Documentation
This directory contains the comprehensive documentation for the Jolt Physics Engine APIs that was previously located in the `index/` directory. This documentation has been moved here to maintain clear separation between interface code and documentation.

**Contents:**
- `README.md` - Main API overview and navigation
- `quick-start.md` - Complete getting started example  
- `api-reference.md` - All 212 classes by category
- `interface-map.md` - Quick lookup and search
- `navigation.md` - Documentation navigation guide
- `bodies/` - Bodies & shapes documentation (120 classes)
- `constraints/` - Constraints documentation (25 classes)
- `core/` - Core infrastructure documentation (57 classes)
- `physics/` - Physics system documentation (12 classes)

## Migration Note

**Previous Location:** `index/` directory (contained documentation only)  
**New Location:** `docs/api/` directory  
**New Purpose of `index/`:** Universal physics engine abstraction layer

The `index/` directory has been completely transformed from a documentation-only location into a proper code abstraction layer that provides universal interfaces for physics engines. This aligns with the project's goal of creating a physics engine abstraction layer rather than just documentation.

## Key Changes

1. **Documentation Moved:** All Jolt-specific API documentation moved from `index/` to `docs/api/`
2. **Interface Layer Added:** `index/` now contains C++ headers defining abstract physics interfaces  
3. **Engine Abstraction:** New abstraction layer supports multiple physics engines with unified API
4. **Implementation Separation:** Clear distinction between interface (abstract) and implementation (concrete)

## Using the Documentation

- **For API Reference:** Browse the `api/` directory for comprehensive Jolt Physics documentation
- **For Abstraction Layer:** See `index/README.md` for the new universal physics interface documentation
- **For Migration:** Existing code using Jolt directly remains unchanged; new code can use the abstraction layer

This restructuring maintains all existing documentation while enabling the creation of a proper physics engine abstraction layer as requested.