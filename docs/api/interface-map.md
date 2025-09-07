# Interface Map - All Jolt Physics Classes

Quick lookup table for finding any class in the Jolt Physics Engine. This comprehensive index covers all 212 exported classes.

## Search by Name

### A
- **AABox** → `Geometry/AABox.h` - Axis-aligned bounding box
- **AABBTreeBuilder** → `AABBTree/AABBTreeBuilder.h` - AABB tree construction
- **Array** → `Core/Array.h` - Dynamic array container

### B  
- **Body** → `Physics/Body/Body.h` - Main rigid body class
- **BodyAccess** → `Physics/Body/BodyAccess.h` - Direct body access
- **BodyCreationSettings** → `Physics/Body/BodyCreationSettings.h` - Body creation configuration
- **BodyFilter** → `Physics/Body/BodyFilter.h` - Body filtering interface
- **BodyInterface** → `Physics/Body/BodyInterface.h` - Thread-safe body operations
- **BodyLock** → `Physics/Body/BodyLock.h` - RAII body locking
- **BodyManager** → `Physics/Body/BodyManager.h` - Body lifecycle management
- **BoxShape** → `Physics/Collision/Shape/BoxShape.h` - Box collision shape
- **BroadPhase** → `Physics/Collision/BroadPhase/BroadPhase.h` - Broad phase collision detection

### C
- **CapsuleShape** → `Physics/Collision/Shape/CapsuleShape.h` - Capsule collision shape
- **Character** → `Physics/Character/Character.h` - Character controller base
- **CollisionCollector** → `Physics/Collision/CollisionCollector.h` - Collision result collection
- **CompoundShape** → `Physics/Collision/Shape/CompoundShape.h` - Container for multiple shapes
- **Constraint** → `Physics/Constraints/Constraint.h` - Abstract base for constraints
- **ConstraintManager** → `Physics/Constraints/ConstraintManager.h` - Constraint management
- **ContactListener** → `Physics/Collision/ContactListener.h` - Contact event interface
- **ConvexHullShape** → `Physics/Collision/Shape/ConvexHullShape.h` - Convex hull collision shape
- **ConvexShape** → `Physics/Collision/Shape/ConvexShape.h` - Base for convex shapes
- **CylinderShape** → `Physics/Collision/Shape/CylinderShape.h` - Cylinder collision shape

### D
- **DebugRenderer** → `Renderer/DebugRenderer.h` - Debug visualization interface
- **DistanceConstraint** → `Physics/Constraints/DistanceConstraint.h` - Distance/spring joint
- **DVec3** → `Math/DVec3.h` - Double precision 3D vector

### E-F
- **Factory** → `Core/Factory.h` - Object creation and registration
- **FixedConstraint** → `Physics/Constraints/FixedConstraint.h` - Fixed/weld joint
- **Float3** → `Math/Float3.h` - 3-component float vector

### G-H
- **HashTable** → `Core/HashTable.h` - Hash table container
- **HeightFieldShape** → `Physics/Collision/Shape/HeightFieldShape.h` - Height field terrain shape
- **HingeConstraint** → `Physics/Constraints/HingeConstraint.h` - Hinge/revolute joint

### I-J
- **IndexedTriangle** → `Geometry/IndexedTriangle.h` - Indexed triangle
- **JobSystem** → `Core/JobSystem.h` - Abstract job execution system
- **JobSystemThreadPool** → `Core/JobSystemThreadPool.h` - Multi-threaded job executor

### K-L
- **LockFreeHashMap** → `Core/LockFreeHashMap.h` - Lock-free hash map

### M
- **Mat44** → `Math/Mat44.h` - 4x4 matrix
- **MassProperties** → `Physics/Body/MassProperties.h` - Mass and inertia properties
- **MeshShape** → `Physics/Collision/Shape/MeshShape.h` - Triangle mesh collision shape
- **MotionProperties** → `Physics/Body/MotionProperties.h` - Dynamic body properties
- **MotorSettings** → `Physics/Constraints/MotorSettings.h` - Motor configuration
- **MutableCompoundShape** → `Physics/Collision/Shape/MutableCompoundShape.h` - Mutable compound shape

### N-O
- **NarrowPhaseQuery** → `Physics/Collision/NarrowPhaseQuery.h` - Detailed collision queries
- **NonCopyable** → `Core/NonCopyable.h` - Non-copyable base class
- **ObjectStream** → `ObjectStream/ObjectStream.h` - Object serialization
- **OrientedBox** → `Geometry/OrientedBox.h` - Oriented bounding box

### P
- **PhysicsSystem** → `Physics/PhysicsSystem.h` - Main physics world controller
- **PhysicsSettings** → `Physics/PhysicsSettings.h` - Physics simulation settings
- **Plane** → `Geometry/Plane.h` - 3D plane
- **PointConstraint** → `Physics/Constraints/PointConstraint.h` - Point-to-point joint
- **Profiler** → `Core/Profiler.h` - Performance profiling

### Q
- **Quat** → `Math/Quat.h` - Quaternion rotation

### R
- **RefTarget** → `Core/Reference.h` - Reference counting base class
- **RTTI** → `Core/RTTI.h` - Runtime type information

### S
- **Shape** → `Physics/Collision/Shape/Shape.h` - Abstract base for all shapes
- **SixDOFConstraint** → `Physics/Constraints/SixDOFConstraint.h` - Six degree of freedom joint
- **SliderConstraint** → `Physics/Constraints/SliderConstraint.h` - Slider/prismatic joint
- **SoftBodyCreationSettings** → `Physics/SoftBody/SoftBodyCreationSettings.h` - Soft body creation settings
- **SphereShape** → `Physics/Collision/Shape/SphereShape.h` - Sphere collision shape
- **SpringSettings** → `Physics/Constraints/SpringSettings.h` - Spring configuration
- **StaticArray** → `Core/StaticArray.h` - Fixed-size array
- **StaticCompoundShape** → `Physics/Collision/Shape/StaticCompoundShape.h` - Static compound shape
- **StateRecorder** → `Physics/StateRecorder.h` - Physics state recording
- **STLAllocator** → `Core/STLAllocator.h` - STL-compatible allocator
- **StreamIn** → `Core/StreamIn.h` - Input stream interface
- **StreamOut** → `Core/StreamOut.h` - Output stream interface
- **SwingTwistConstraint** → `Physics/Constraints/SwingTwistConstraint.h` - Swing-twist joint

### T
- **TempAllocator** → `Core/TempAllocator.h` - Fast temporary memory allocator
- **Triangle** → `Geometry/Triangle.h` - 3D triangle
- **TwoBodyConstraint** → `Physics/Constraints/TwoBodyConstraint.h` - Constraint between two bodies

### U-V
- **UVec4** → `Math/UVec4.h` - 4D unsigned integer vector
- **Vec3** → `Math/Vec3.h` - 3D vector
- **Vec4** → `Math/Vec4.h` - 4D vector
- **VehicleController** → `Physics/Vehicle/VehicleController.h` - Vehicle simulation controller
- **VehicleEngine** → `Physics/Vehicle/VehicleEngine.h` - Vehicle engine simulation

### W-Z
- **Wheel** → `Physics/Vehicle/Wheel.h` - Vehicle wheel simulation

## Search by Category

### Core System (Foundation - Must Know)
- `Factory` - Object creation system
- `JobSystemThreadPool` - Multi-threading
- `TempAllocator` - Memory management
- `RTTI` - Type information
- `RefTarget` - Reference counting

### Physics World (Essential)
- `PhysicsSystem` - Main physics controller
- `BodyInterface` - Body operations
- `PhysicsSettings` - Configuration
- `BodyCreationSettings` - Body setup

### Shapes (Essential)
- `Shape` - Base class
- `BoxShape` - Most common shape
- `SphereShape` - Simple physics
- `CapsuleShape` - Character physics
- `MeshShape` - Complex static geometry
- `CompoundShape` - Complex dynamic objects

### Bodies (Essential)
- `Body` - The rigid body
- `BodyID` - Body identifier
- `MotionProperties` - Dynamic properties
- `MassProperties` - Mass/inertia

### Constraints (Common)
- `Constraint` - Base class
- `FixedConstraint` - Weld joints
- `HingeConstraint` - Door/wheel joints
- `DistanceConstraint` - Springs
- `PointConstraint` - Ball joints

### Collision (Common)
- `NarrowPhaseQuery` - Collision queries
- `ContactListener` - Collision events
- `BroadPhase` - Broad phase system
- `CollisionCollector` - Result collection

### Math (Common)
- `Vec3` - 3D vectors
- `Quat` - Rotations
- `Mat44` - Matrices
- `Float3` - Simple vectors

### Advanced Features
- `Character` - Character controllers
- `VehicleController` - Vehicle physics
- `SoftBodyCreationSettings` - Soft bodies
- `StateRecorder` - Deterministic recording

### Utilities (As Needed)
- `DebugRenderer` - Visualization
- `Profiler` - Performance analysis
- `ObjectStream` - Serialization

## Quick Reference by Use Case

### "I want to create a simple physics world"
1. `Factory` - Initialize system
2. `JobSystemThreadPool` - Threading
3. `PhysicsSystem` - Physics world
4. `BodyInterface` - Create objects
5. `BoxShape`/`SphereShape` - Simple shapes

### "I want to make a character controller"
1. Start with simple physics world (above)
2. `Character` - Character controller
3. `CapsuleShape` - Character collision
4. `CharacterContactListener` - Character events

### "I want to make a vehicle"
1. Start with simple physics world
2. `VehicleController` - Vehicle system
3. `WheeledVehicleController` - Car-like vehicle
4. `VehicleEngine` - Engine simulation
5. `Wheel` - Wheel physics

### "I want to connect objects with joints"
1. Start with simple physics world
2. `HingeConstraint` - Doors, wheels
3. `DistanceConstraint` - Springs, ropes
4. `FixedConstraint` - Weld objects together
5. `PointConstraint` - Ball joints

### "I want collision detection without physics"
1. `Factory` - Initialize
2. `Shape` classes - Define geometry
3. `NarrowPhaseQuery` - Query interface
4. `CollisionCollector` - Collect results

### "I want to debug/visualize physics"
1. `DebugRenderer` - Visualization interface
2. `BodyDrawFilter` - Control what's drawn
3. `Profiler` - Performance analysis

## Integration Checklist

✅ **Basic Setup**
- [ ] Call `RegisterDefaultAllocator()`
- [ ] Create `Factory::sInstance`
- [ ] Call `RegisterTypes()`
- [ ] Create `JobSystemThreadPool`
- [ ] Create `PhysicsSystem`

✅ **Layer Configuration**
- [ ] Define object layers
- [ ] Define broad phase layers
- [ ] Implement layer filters
- [ ] Configure collision matrix

✅ **Body Creation**
- [ ] Create shapes (reuse when possible)
- [ ] Configure `BodyCreationSettings`
- [ ] Use `BodyInterface` for operations
- [ ] Set appropriate motion types

✅ **Cleanup**
- [ ] Remove all bodies
- [ ] Remove all constraints
- [ ] Delete `Factory::sInstance`
- [ ] Call `UnregisterTypes()`

This index provides quick access to any class in Jolt Physics. Use the search functions or browse by category to find what you need!