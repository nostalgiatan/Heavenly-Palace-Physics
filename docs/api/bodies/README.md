# Bodies & Shapes APIs

Complete reference for rigid bodies, collision shapes, and related systems in Jolt Physics.

## Body System Overview

Bodies are the fundamental simulation objects that have mass, position, and velocity. Shapes define the collision geometry of bodies.

### Core Body Classes
- **Body** - The main rigid body class
- **BodyCreationSettings** - Configuration for creating bodies
- **BodyInterface** - Thread-safe interface for body operations
- **BodyManager** - Internal body management system
- **BodyID** - Unique identifier for bodies

### Body Types by Motion
- **Static** - Non-moving objects (terrain, walls)
- **Kinematic** - Animated objects (moving platforms)
- **Dynamic** - Physically simulated objects

## Shape System

### Base Shape Classes
- **Shape** - Abstract base class for all shapes
- **ConvexShape** - Base for convex shapes (efficient collision)
- **CompoundShape** - Container for multiple shapes

### Primitive Shapes
```cpp
// Box shape
BoxShapeSettings box_settings(Vec3(1.0f, 1.0f, 1.0f));
Ref<Shape> box_shape = box_settings.Create().Get();

// Sphere shape  
SphereShapeSettings sphere_settings(1.0f);
Ref<Shape> sphere_shape = sphere_settings.Create().Get();

// Capsule shape
CapsuleShapeSettings capsule_settings(2.0f, 0.5f); // height, radius
Ref<Shape> capsule_shape = capsule_settings.Create().Get();
```

| Shape Type | Class | Best Use Case |
|------------|-------|---------------|
| **Box** | `BoxShape` | Crates, buildings, simple objects |
| **Sphere** | `SphereShape` | Balls, planets, particles |
| **Capsule** | `CapsuleShape` | Characters, pills, rods |
| **Cylinder** | `CylinderShape` | Barrels, columns, wheels |
| **Convex Hull** | `ConvexHullShape` | Complex convex objects |

### Complex Shapes
```cpp
// Mesh shape (for static geometry)
TriangleList triangles;
// ... populate triangles
MeshShapeSettings mesh_settings(triangles);
Ref<Shape> mesh_shape = mesh_settings.Create().Get();

// Compound shape (multiple shapes in one)
StaticCompoundShapeSettings compound_settings;
compound_settings.AddShape(Vec3(0, 0, 0), Quat::sIdentity(), box_shape);
compound_settings.AddShape(Vec3(2, 0, 0), Quat::sIdentity(), sphere_shape);
Ref<Shape> compound_shape = compound_settings.Create().Get();
```

| Shape Type | Class | Best Use Case |
|------------|-------|---------------|
| **Mesh** | `MeshShape` | Complex static geometry (terrain, buildings) |
| **Heightfield** | `HeightFieldShape` | Terrain, landscapes |
| **Compound** | `CompoundShape` | Complex objects made of multiple shapes |

## Body Creation

### Basic Body Creation
```cpp
// Create a dynamic box
BodyCreationSettings body_settings(
    new BoxShape(Vec3(0.5f, 0.5f, 0.5f)),    // Shape
    RVec3(0, 10, 0),                          // Position
    Quat::sIdentity(),                        // Rotation
    EMotionType::Dynamic,                     // Motion type
    Layers::MOVING                            // Object layer
);

// Set additional properties
body_settings.mRestitution = 0.8f;           // Bounciness
body_settings.mFriction = 0.5f;              // Friction
body_settings.mLinearDamping = 0.01f;        // Linear damping
body_settings.mAngularDamping = 0.01f;       // Angular damping

// Create and add to world
BodyInterface& body_interface = physics_system.GetBodyInterface();
BodyID body_id = body_interface.CreateAndAddBody(body_settings, EActivation::Activate);
```

### Motion Types
```cpp
// Static body (never moves)
body_settings.mMotionType = EMotionType::Static;

// Kinematic body (moves but not affected by forces)
body_settings.mMotionType = EMotionType::Kinematic;

// Dynamic body (full physics simulation)
body_settings.mMotionType = EMotionType::Dynamic;
```

### Mass Properties
```cpp
// Automatic mass calculation from shape
body_settings.mOverrideMassProperties = EOverrideMassProperties::CalculateInertia;
body_settings.mMassPropertiesOverride.mMass = 10.0f;

// Custom mass and inertia
MassProperties mass_props;
mass_props.mMass = 5.0f;
mass_props.mInertia = Mat44::sRotationTranslation(Quat::sIdentity(), Vec3::sZero());
body_settings.mOverrideMassProperties = EOverrideMassProperties::MassAndInertiaProvided;
body_settings.mMassPropertiesOverride = mass_props;
```

## Body Operations

### Position and Rotation
```cpp
// Get current transform
RVec3 position = body_interface.GetPosition(body_id);
Quat rotation = body_interface.GetRotation(body_id);
RMat44 transform = body_interface.GetWorldTransform(body_id);

// Set new transform
body_interface.SetPosition(body_id, RVec3(0, 5, 0), EActivation::Activate);
body_interface.SetRotation(body_id, Quat::sRotation(Vec3::sAxisY(), JPH_PI), EActivation::Activate);
body_interface.SetPositionAndRotation(body_id, RVec3(1, 2, 3), Quat::sIdentity(), EActivation::Activate);
```

### Velocity and Forces
```cpp
// Get velocity
Vec3 linear_velocity = body_interface.GetLinearVelocity(body_id);
Vec3 angular_velocity = body_interface.GetAngularVelocity(body_id);

// Set velocity
body_interface.SetLinearVelocity(body_id, Vec3(5, 0, 0));
body_interface.SetAngularVelocity(body_id, Vec3(0, 1, 0));

// Apply forces (accumulated until next physics step)
body_interface.AddForce(body_id, Vec3(0, 1000, 0));                    // Force at center of mass
body_interface.AddForce(body_id, Vec3(100, 0, 0), RVec3(0, 1, 0));     // Force at world position
body_interface.AddTorque(body_id, Vec3(0, 50, 0));                     // Torque

// Apply impulses (immediate velocity change)
body_interface.AddImpulse(body_id, Vec3(0, 10, 0));                    // Impulse at center of mass
body_interface.AddImpulse(body_id, Vec3(5, 0, 0), RVec3(0, 1, 0));     // Impulse at world position
body_interface.AddAngularImpulse(body_id, Vec3(0, 2, 0));              // Angular impulse
```

### Body Properties
```cpp
// Motion type
body_interface.SetMotionType(body_id, EMotionType::Kinematic, EActivation::Activate);

// Activation/deactivation
body_interface.ActivateBody(body_id);
body_interface.DeactivateBody(body_id);
bool is_active = body_interface.IsActive(body_id);

// Material properties
body_interface.SetRestitution(body_id, 0.9f);
body_interface.SetFriction(body_id, 0.3f);

// Gravity
body_interface.SetGravityFactor(body_id, 0.5f);  // Half gravity
```

## Shape Creation Best Practices

### Performance Considerations
```cpp
// Good: Share shapes between bodies
Ref<Shape> box_shape = new BoxShape(Vec3(1, 1, 1));
for (int i = 0; i < 100; ++i) {
    BodyCreationSettings settings(box_shape, positions[i], Quat::sIdentity(), 
                                 EMotionType::Dynamic, Layers::MOVING);
    body_interface.CreateAndAddBody(settings, EActivation::Activate);
}

// Avoid: Creating new shapes for each body (wasteful)
for (int i = 0; i < 100; ++i) {
    Ref<Shape> box_shape = new BoxShape(Vec3(1, 1, 1));  // Creates 100 identical shapes!
    // ... create body
}
```

### Shape Selection Guidelines
- **Convex shapes** (Box, Sphere, Capsule, ConvexHull) are fastest for collision detection
- **Mesh shapes** should only be used for static geometry
- **Compound shapes** allow complex objects while maintaining good performance
- **Use the simplest shape** that provides acceptable collision behavior

### Memory Management
```cpp
// Shapes are reference counted - store in Ref<>
Ref<Shape> shape = new BoxShape(Vec3(1, 1, 1));

// Shape settings can be temporary
{
    BoxShapeSettings settings(Vec3(1, 1, 1));
    settings.mConvexRadius = 0.05f;  // Optional: adjust collision margin
    Ref<Shape> shape = settings.Create().Get();
}  // settings destroyed, but shape remains valid
```

## Complete Example

```cpp
// Complete body creation example
void CreatePhysicsObjects(PhysicsSystem& physics_system)
{
    BodyInterface& body_interface = physics_system.GetBodyInterface();

    // Create ground (static mesh)
    {
        TriangleList triangles;
        triangles.push_back(Triangle(Float3(-100, 0, -100), Float3(100, 0, -100), Float3(-100, 0, 100)));
        triangles.push_back(Triangle(Float3(100, 0, -100), Float3(100, 0, 100), Float3(-100, 0, 100)));
        
        MeshShapeSettings ground_settings(triangles);
        BodyCreationSettings ground_body(ground_settings.Create().Get(), RVec3::sZero(), 
                                        Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
        body_interface.CreateAndAddBody(ground_body, EActivation::DontActivate);
    }

    // Create dynamic objects
    Ref<Shape> box_shape = new BoxShape(Vec3(0.5f, 0.5f, 0.5f));
    for (int i = 0; i < 10; ++i)
    {
        BodyCreationSettings body_settings(box_shape, RVec3(0, 5 + i * 2, 0), 
                                          Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
        body_settings.mRestitution = 0.7f;
        body_settings.mFriction = 0.5f;
        
        body_interface.CreateAndAddBody(body_settings, EActivation::Activate);
    }
}
```

## Related Documentation
- [Physics System Setup](../physics/getting-started.md)
- [Collision Detection](../collision/overview.md)
- [Shape Reference](shapes.md)
- [Body Creation Guide](creating-bodies.md)