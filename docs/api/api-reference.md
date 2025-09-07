# Complete API Reference

This is the comprehensive reference for all 212 exported classes in Jolt Physics Engine, organized by category.

## Core Infrastructure (57 classes)

### Memory Management
| Class | Header | Purpose |
|-------|--------|---------|
| `TempAllocator` | `Core/TempAllocator.h` | Fast temporary memory allocator |
| `TempAllocatorImpl` | `Core/TempAllocator.h` | Implementation of temp allocator |
| `TempAllocatorMalloc` | `Core/TempAllocator.h` | Malloc-based temp allocator |
| `STLAllocator` | `Core/STLAllocator.h` | STL-compatible allocator |
| `STLTempAllocator` | `Core/STLTempAllocator.h` | STL-compatible temp allocator |
| `FixedSizeFreeList` | `Core/FixedSizeFreeList.h` | Fixed-size object pool |

### Job System
| Class | Header | Purpose |
|-------|--------|---------|
| `JobSystem` | `Core/JobSystem.h` | Abstract job execution system |
| `JobSystemThreadPool` | `Core/JobSystemThreadPool.h` | Multi-threaded job executor |
| `JobSystemSingleThreaded` | `Core/JobSystemSingleThreaded.h` | Single-threaded job system |
| `JobSystemWithBarrier` | `Core/JobSystemWithBarrier.h` | Job system with synchronization |
| `Job` | `Core/JobSystem.h` | Base class for jobs |
| `JobHandle` | `Core/JobSystem.h` | Handle to queued job |

### Object System
| Class | Header | Purpose |
|-------|--------|---------|
| `RTTI` | `Core/RTTI.h` | Runtime type information |
| `Factory` | `Core/Factory.h` | Object creation and registration |
| `RefTarget` | `Core/Reference.h` | Reference counting base class |
| `RefTargetVirtual` | `Core/Reference.h` | Virtual reference counting base |
| `NonCopyable` | `Core/NonCopyable.h` | Non-copyable base class |

### Containers & Utilities
| Class | Header | Purpose |
|-------|--------|---------|
| `Array` | `Core/Array.h` | Dynamic array container |
| `StaticArray` | `Core/StaticArray.h` | Fixed-size array |
| `HashTable` | `Core/HashTable.h` | Hash table container |
| `LockFreeHashMap` | `Core/LockFreeHashMap.h` | Lock-free hash map |
| `UnorderedMap` | `Core/UnorderedMap.h` | Unordered map wrapper |
| `UnorderedSet` | `Core/UnorderedSet.h` | Unordered set wrapper |

## Physics System (12 classes)

### Main System
| Class | Header | Purpose |
|-------|--------|---------|
| `PhysicsSystem` | `Physics/PhysicsSystem.h` | Main physics world controller |
| `PhysicsSettings` | `Physics/PhysicsSettings.h` | Physics simulation settings |
| `PhysicsUpdateContext` | `Physics/PhysicsUpdateContext.h` | Update context information |
| `PhysicsStepListener` | `Physics/PhysicsStepListener.h` | Physics step event interface |

### System Management
| Class | Header | Purpose |
|-------|--------|---------|
| `BodyManager` | `Physics/Body/BodyManager.h` | Body lifecycle management |
| `ConstraintManager` | `Physics/Constraints/ConstraintManager.h` | Constraint management |
| `ContactConstraintManager` | `Physics/Constraints/ContactConstraintManager.h` | Contact constraint handling |
| `IslandBuilder` | `Physics/IslandBuilder.h` | Simulation island construction |

## Body System (31 classes)

### Core Body Classes
| Class | Header | Purpose |
|-------|--------|---------|
| `Body` | `Physics/Body/Body.h` | Main rigid body class |
| `BodyCreationSettings` | `Physics/Body/BodyCreationSettings.h` | Body creation configuration |
| `BodyInterface` | `Physics/Body/BodyInterface.h` | Thread-safe body operations |
| `BodyLockInterface` | `Physics/Body/BodyLockInterface.h` | Body locking interface |
| `BodyID` | `Physics/Body/BodyID.h` | Unique body identifier |

### Body Management
| Class | Header | Purpose |
|-------|--------|---------|
| `BodyAccess` | `Physics/Body/BodyAccess.h` | Direct body access |
| `BodyLock` | `Physics/Body/BodyLock.h` | RAII body locking |
| `BodyLockRead` | `Physics/Body/BodyLock.h` | Read-only body lock |
| `BodyLockWrite` | `Physics/Body/BodyLock.h` | Write body lock |
| `BodyFilter` | `Physics/Body/BodyFilter.h` | Body filtering interface |

### Motion Properties
| Class | Header | Purpose |
|-------|--------|---------|
| `MotionProperties` | `Physics/Body/MotionProperties.h` | Dynamic body properties |
| `MassProperties` | `Physics/Body/MassProperties.h` | Mass and inertia properties |

## Shape System (89 classes)

### Base Shape Classes
| Class | Header | Purpose |
|-------|--------|---------|
| `Shape` | `Physics/Collision/Shape/Shape.h` | Abstract base for all shapes |
| `ConvexShape` | `Physics/Collision/Shape/ConvexShape.h` | Base for convex shapes |
| `CompoundShape` | `Physics/Collision/Shape/CompoundShape.h` | Container for multiple shapes |

### Primitive Shapes
| Class | Header | Purpose |
|-------|--------|---------|
| `BoxShape` | `Physics/Collision/Shape/BoxShape.h` | Box/cube collision shape |
| `BoxShapeSettings` | `Physics/Collision/Shape/BoxShape.h` | Box shape creation settings |
| `SphereShape` | `Physics/Collision/Shape/SphereShape.h` | Sphere collision shape |
| `SphereShapeSettings` | `Physics/Collision/Shape/SphereShape.h` | Sphere shape creation settings |
| `CapsuleShape` | `Physics/Collision/Shape/CapsuleShape.h` | Capsule collision shape |
| `CapsuleShapeSettings` | `Physics/Collision/Shape/CapsuleShape.h` | Capsule shape creation settings |
| `CylinderShape` | `Physics/Collision/Shape/CylinderShape.h` | Cylinder collision shape |
| `CylinderShapeSettings` | `Physics/Collision/Shape/CylinderShape.h` | Cylinder shape creation settings |

### Complex Shapes
| Class | Header | Purpose |
|-------|--------|---------|
| `ConvexHullShape` | `Physics/Collision/Shape/ConvexHullShape.h` | Convex hull collision shape |
| `ConvexHullShapeSettings` | `Physics/Collision/Shape/ConvexHullShape.h` | Convex hull creation settings |
| `MeshShape` | `Physics/Collision/Shape/MeshShape.h` | Triangle mesh collision shape |
| `MeshShapeSettings` | `Physics/Collision/Shape/MeshShape.h` | Mesh shape creation settings |
| `HeightFieldShape` | `Physics/Collision/Shape/HeightFieldShape.h` | Height field terrain shape |
| `HeightFieldShapeSettings` | `Physics/Collision/Shape/HeightFieldShape.h` | Height field creation settings |

### Compound Shapes
| Class | Header | Purpose |
|-------|--------|---------|
| `StaticCompoundShape` | `Physics/Collision/Shape/StaticCompoundShape.h` | Static compound shape |
| `StaticCompoundShapeSettings` | `Physics/Collision/Shape/StaticCompoundShape.h` | Static compound creation settings |
| `MutableCompoundShape` | `Physics/Collision/Shape/MutableCompoundShape.h` | Mutable compound shape |
| `MutableCompoundShapeSettings` | `Physics/Collision/Shape/MutableCompoundShape.h` | Mutable compound creation settings |

## Collision Detection (15 classes)

### Broad Phase
| Class | Header | Purpose |
|-------|--------|---------|
| `BroadPhase` | `Physics/Collision/BroadPhase/BroadPhase.h` | Broad phase collision detection |
| `BroadPhaseQuery` | `Physics/Collision/BroadPhase/BroadPhaseQuery.h` | Broad phase query interface |
| `BroadPhaseLayerInterface` | `Physics/Collision/BroadPhase/BroadPhaseLayerInterface.h` | Broad phase layer mapping |
| `BroadPhaseLayerFilter` | `Physics/Collision/BroadPhase/BroadPhaseLayerFilter.h` | Broad phase layer filtering |

### Narrow Phase
| Class | Header | Purpose |
|-------|--------|---------|
| `NarrowPhaseQuery` | `Physics/Collision/NarrowPhaseQuery.h` | Detailed collision queries |
| `CollisionCollector` | `Physics/Collision/CollisionCollector.h` | Collision result collection |
| `CastRayCollector` | `Physics/Collision/CastRayCollector.h` | Ray casting result collector |
| `CollideShapeCollector` | `Physics/Collision/CollideShapeCollector.h` | Shape collision collector |

### Contact Management
| Class | Header | Purpose |
|-------|--------|---------|
| `ContactListener` | `Physics/Collision/ContactListener.h` | Contact event interface |
| `ContactManifold` | `Physics/Collision/ContactManifold.h` | Contact point collection |
| `ContactSettings` | `Physics/Collision/ContactSettings.h` | Contact behavior settings |

## Constraint System (25 classes)

### Base Constraint Classes
| Class | Header | Purpose |
|-------|--------|---------|
| `Constraint` | `Physics/Constraints/Constraint.h` | Abstract base for constraints |
| `TwoBodyConstraint` | `Physics/Constraints/TwoBodyConstraint.h` | Constraint between two bodies |
| `ConstraintSettings` | `Physics/Constraints/ConstraintSettings.h` | Constraint creation settings |

### Joint Types
| Class | Header | Purpose |
|-------|--------|---------|
| `FixedConstraint` | `Physics/Constraints/FixedConstraint.h` | Fixed/weld joint |
| `PointConstraint` | `Physics/Constraints/PointConstraint.h` | Point-to-point joint |
| `DistanceConstraint` | `Physics/Constraints/DistanceConstraint.h` | Distance/spring joint |
| `HingeConstraint` | `Physics/Constraints/HingeConstraint.h` | Hinge/revolute joint |
| `SliderConstraint` | `Physics/Constraints/SliderConstraint.h` | Slider/prismatic joint |
| `ConeConstraint` | `Physics/Constraints/ConeConstraint.h` | Cone constraint |
| `SwingTwistConstraint` | `Physics/Constraints/SwingTwistConstraint.h` | Swing-twist joint |
| `SixDOFConstraint` | `Physics/Constraints/SixDOFConstraint.h` | Six degree of freedom joint |

### Motors
| Class | Header | Purpose |
|-------|--------|---------|
| `MotorSettings` | `Physics/Constraints/MotorSettings.h` | Motor configuration |
| `SpringSettings` | `Physics/Constraints/SpringSettings.h` | Spring configuration |

## Math & Geometry (35 classes)

### Vector Math
| Class | Header | Purpose |
|-------|--------|---------|
| `Vec3` | `Math/Vec3.h` | 3D vector |
| `Vec4` | `Math/Vec4.h` | 4D vector |
| `UVec4` | `Math/UVec4.h` | 4D unsigned integer vector |
| `DVec3` | `Math/DVec3.h` | Double precision 3D vector |
| `Float3` | `Math/Float3.h` | 3-component float vector |

### Matrix Math
| Class | Header | Purpose |
|-------|--------|---------|
| `Mat44` | `Math/Mat44.h` | 4x4 matrix |
| `DMat44` | `Math/DMat44.h` | Double precision 4x4 matrix |
| `Quat` | `Math/Quat.h` | Quaternion rotation |

### Geometry
| Class | Header | Purpose |
|-------|--------|---------|
| `AABox` | `Geometry/AABox.h` | Axis-aligned bounding box |
| `OrientedBox` | `Geometry/OrientedBox.h` | Oriented bounding box |
| `Plane` | `Geometry/Plane.h` | 3D plane |
| `Triangle` | `Geometry/Triangle.h` | 3D triangle |
| `IndexedTriangle` | `Geometry/IndexedTriangle.h` | Indexed triangle |
| `Sphere` | `Geometry/Sphere.h` | 3D sphere |

## Character Control (8 classes)

### Character System
| Class | Header | Purpose |
|-------|--------|---------|
| `Character` | `Physics/Character/Character.h` | Character controller base |
| `CharacterSettings` | `Physics/Character/Character.h` | Character configuration |
| `CharacterBase` | `Physics/Character/CharacterBase.h` | Character base class |
| `CharacterVirtual` | `Physics/Character/CharacterVirtual.h` | Virtual character controller |

### Character Support
| Class | Header | Purpose |
|-------|--------|---------|
| `CharacterContactListener` | `Physics/Character/CharacterContactListener.h` | Character contact events |
| `CharacterContactSettings` | `Physics/Character/CharacterContactSettings.h` | Character contact configuration |

## Vehicle System (15 classes)

### Vehicle Core
| Class | Header | Purpose |
|-------|--------|---------|
| `VehicleController` | `Physics/Vehicle/VehicleController.h` | Vehicle simulation controller |
| `VehicleConstraint` | `Physics/Vehicle/VehicleConstraint.h` | Vehicle constraint system |
| `WheeledVehicleController` | `Physics/Vehicle/WheeledVehicleController.h` | Wheeled vehicle controller |

### Vehicle Components
| Class | Header | Purpose |
|-------|--------|---------|
| `VehicleEngine` | `Physics/Vehicle/VehicleEngine.h` | Vehicle engine simulation |
| `VehicleTransmission` | `Physics/Vehicle/VehicleTransmission.h` | Vehicle transmission |
| `VehicleDifferential` | `Physics/Vehicle/VehicleDifferential.h` | Vehicle differential |
| `Wheel` | `Physics/Vehicle/Wheel.h` | Vehicle wheel simulation |

## Soft Body System (8 classes)

### Soft Body Core
| Class | Header | Purpose |
|-------|--------|---------|
| `SoftBodyCreationSettings` | `Physics/SoftBody/SoftBodyCreationSettings.h` | Soft body creation settings |
| `SoftBodySharedSettings` | `Physics/SoftBody/SoftBodySharedSettings.h` | Shared soft body settings |
| `SoftBodyContactListener` | `Physics/SoftBody/SoftBodyContactListener.h` | Soft body contact events |

## Utilities & Tools (12 classes)

### Debugging
| Class | Header | Purpose |
|-------|--------|---------|
| `DebugRenderer` | `Renderer/DebugRenderer.h` | Debug visualization interface |
| `BodyDrawFilter` | `Physics/Body/BodyDrawFilter.h` | Body rendering filter |

### Serialization
| Class | Header | Purpose |
|-------|--------|---------|
| `StateRecorder` | `Physics/StateRecorder.h` | Physics state recording |
| `ObjectStream` | `ObjectStream/ObjectStream.h` | Object serialization |
| `StreamIn` | `Core/StreamIn.h` | Input stream interface |
| `StreamOut` | `Core/StreamOut.h` | Output stream interface |

### Profiling
| Class | Header | Purpose |
|-------|--------|---------|
| `Profiler` | `Core/Profiler.h` | Performance profiling |
| `ProfileSample` | `Core/Profiler.h` | Profiling sample |

## Usage Priority

### Essential (Must Know)
- `PhysicsSystem`, `BodyInterface`, `JobSystemThreadPool`
- `BoxShape`, `SphereShape`, `CapsuleShape`
- `BodyCreationSettings`, `Vec3`, `Quat`

### Common (Frequently Used)
- `MeshShape`, `CompoundShape`, `ConvexHullShape`
- `ContactListener`, `NarrowPhaseQuery`
- `FixedConstraint`, `HingeConstraint`, `DistanceConstraint`

### Advanced (Specialized)
- `Character`, `VehicleController`, `SoftBodyCreationSettings`
- Custom shapes, advanced constraints, debug rendering

### Internal (Use with Caution)
- `BodyManager`, `ConstraintManager`, `IslandBuilder`
- Low-level collision detection internals