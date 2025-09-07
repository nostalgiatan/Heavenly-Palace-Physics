# Physics System APIs

The main physics simulation system that manages the physics world, handles updates, and coordinates all physics objects.

## Essential Physics Classes

### Main System
- **PhysicsSystem** - The central physics world manager
- **PhysicsSettings** - Configuration settings for the physics system
- **PhysicsUpdateContext** - Context information during physics updates
- **PhysicsStepListener** - Interface for monitoring physics steps

### World Management
- **BodyManager** - Manages all bodies in the physics world
- **ConstraintManager** - Manages all constraints
- **ContactConstraintManager** - Manages contact constraints
- **IslandBuilder** - Builds simulation islands for optimization

## Core Physics System API

### PhysicsSystem
```cpp
// Create and initialize physics system
const uint cMaxBodies = 65536;
const uint cMaxBodyPairs = 65536;
const uint cMaxContactConstraints = 10240;

PhysicsSystem physics_system;
physics_system.Init(cMaxBodies, cMaxBodyPairs, cMaxContactConstraints,
                   broad_phase_layer_interface, object_vs_broadphase_layer_filter,
                   object_vs_object_layer_filter);
```

| Method | Purpose | Parameters |
|--------|---------|------------|
| `Init()` | Initialize the physics system | Max bodies, pairs, constraints, filters |
| `Update()` | Step the physics simulation | Delta time, collision steps, job system |
| `GetBodyInterface()` | Get interface for body operations | Thread-safe access type |
| `GetNarrowPhaseQuery()` | Get collision query interface | - |
| `SetContactListener()` | Set collision event listener | Contact listener interface |
| `AddStepListener()` | Add physics step listener | Step listener interface |

### Physics Settings
```cpp
PhysicsSettings settings;
settings.mGravity = Vec3(0, -9.81f, 0);
settings.mNumVelocitySteps = 10;
settings.mNumPositionSteps = 2;
physics_system.SetPhysicsSettings(settings);
```

| Setting | Purpose | Default Value |
|---------|---------|---------------|
| `mGravity` | World gravity vector | (0, -9.81, 0) |
| `mNumVelocitySteps` | Velocity solver iterations | 10 |
| `mNumPositionSteps` | Position solver iterations | 2 |
| `mBaumgarte` | Position correction factor | 0.2f |
| `mSpeculativeContactDistance` | Speculative contact distance | 0.02f |

### Update Loop
```cpp
// Typical physics update
const float deltaTime = 1.0f / 60.0f;
const int collisionSteps = 1;

physics_system.Update(deltaTime, collisionSteps, &job_system, &temp_allocator);
```

## Body Management

### Body Interface
```cpp
// Get thread-safe body interface
BodyInterface& body_interface = physics_system.GetBodyInterface();

// Create a body
BodyCreationSettings body_settings;
body_settings.SetShape(new BoxShape(Vec3(0.5f, 0.5f, 0.5f)));
body_settings.mPosition = RVec3(0, 10, 0);
body_settings.mMotionType = EMotionType::Dynamic;
body_settings.mObjectLayer = Layers::MOVING;

BodyID body_id = body_interface.CreateAndAddBody(body_settings, EActivation::Activate);
```

### Body Operations
```cpp
// Position and rotation
body_interface.SetPosition(body_id, RVec3(0, 5, 0), EActivation::Activate);
body_interface.SetRotation(body_id, Quat::sRotation(Vec3::sAxisY(), 0.25f * JPH_PI), EActivation::Activate);

// Velocity
body_interface.SetLinearVelocity(body_id, Vec3(0, 5, 0));
body_interface.SetAngularVelocity(body_id, Vec3(0, 2, 0));

// Forces
body_interface.AddForce(body_id, Vec3(0, 1000, 0));
body_interface.AddTorque(body_id, Vec3(0, 100, 0));
```

## Collision Filtering

### Layer System
```cpp
// Define object layers
namespace Layers
{
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
};

// Define broad phase layers  
namespace BroadPhaseLayers
{
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
};
```

### Filter Implementation
```cpp
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
    {
        switch (inObject1)
        {
        case Layers::NON_MOVING:
            return inObject2 == Layers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};
```

## Contact Events

### Contact Listener
```cpp
class MyContactListener : public ContactListener
{
public:
    virtual ValidateResult OnContactValidate(const Body &inBody1, const Body &inBody2, 
                                           RVec3Arg inBaseOffset, const CollideShapeResult &inCollisionResult) override
    {
        // Return ValidateResult::AcceptAllContactsForThisBodyPair to accept all contacts
        return ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    virtual void OnContactAdded(const Body &inBody1, const Body &inBody2, 
                               const ContactManifold &inManifold, ContactSettings &ioSettings) override
    {
        // Handle contact added
    }

    virtual void OnContactRemoved(const SubShapeIDPair &inSubShapePair) override
    {
        // Handle contact removed  
    }
};

// Set the listener
MyContactListener contact_listener;
physics_system.SetContactListener(&contact_listener);
```

## Best Practices

1. **Initialize properly** - Always call Init() with appropriate limits
2. **Use consistent time steps** - Fixed time step (1/60s) is recommended
3. **Manage object layers** - Design collision layers carefully for performance
4. **Handle contact events** - Use contact listeners for game logic
5. **Update efficiently** - Use job system for multi-threaded performance
6. **Clean up** - Remove bodies and constraints when no longer needed

## Performance Tips

- Use `EActivation::DontActivate` when creating many static objects
- Implement efficient collision filters to avoid unnecessary collision checks
- Use appropriate broad phase layer counts (typically 2-4)
- Consider using `SetGravity()` per body for special effects
- Use `SetMotionType()` to change between static/kinematic/dynamic

## Related Documentation
- [Body Creation Guide](../bodies/creating-bodies.md)
- [Collision Detection](../collision/overview.md)
- [Constraints](../constraints/README.md)
- [Core APIs](../core/README.md)