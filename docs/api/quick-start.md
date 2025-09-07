# Quick Start Guide

Get started with Jolt Physics Engine in just a few steps. This guide covers the essential setup and basic usage.

## Step 1: Initialize the Core Systems

```cpp
#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

using namespace JPH;

// Initialize Jolt
void InitializeJolt()
{
    // Register allocation hook
    RegisterDefaultAllocator();

    // Create a factory
    Factory::sInstance = new Factory();

    // Register all Jolt physics types
    RegisterTypes();
}
```

## Step 2: Define Collision Layers

```cpp
// Layer that objects can be in, determines which other objects it can collide with
// Typically you at least want to have 1 layer for moving objects and 1 layer for static objects, but you can have more
// layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
// but only if you do collision testing).
namespace Layers
{
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
};

/// Class that determines if two broad phase layers can collide
class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
    BPLayerInterfaceImpl()
    {
        // Create a mapping table from object to broad phase layer
        mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }

    virtual uint GetNumBroadPhaseLayers() const override
    {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override
    {
        JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
        return mObjectToBroadPhase[inLayer];
    }

private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
    {
        switch (inObject1)
        {
        case Layers::NON_MOVING:
            return inObject2 == Layers::MOVING; // Non moving only collides with moving
        case Layers::MOVING:
            return true; // Moving collides with everything
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};

// Each broad phase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broad phase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broad phase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers
{
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
};

/// BroadPhaseLayerInterface implementation
BPLayerInterfaceImpl broad_phase_layer_interface;

/// Class that filters object vs broadphase layers
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override
    {
        switch (inLayer1)
        {
        case Layers::NON_MOVING:
            return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};

ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
ObjectLayerPairFilterImpl object_vs_object_layer_filter;
```

## Step 3: Create Physics System

```cpp
void CreatePhysicsSystem()
{
    // We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
    const uint cMaxBodies = 65536;
    const uint cMaxBodyPairs = 65536;
    const uint cMaxContactConstraints = 10240;

    // Create physics system
    PhysicsSystem physics_system;
    physics_system.Init(cMaxBodies, cMaxBodyPairs, cMaxContactConstraints, 
                       broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

    // A body activation listener gets notified when bodies activate and go to sleep
    // Note that this is called from a job so whatever you do here needs to be thread safe.
    // Registering one is entirely optional.
    MyBodyActivationListener body_activation_listener;
    physics_system.SetBodyActivationListener(&body_activation_listener);

    // A contact listener gets notified when bodies (are about to) collide, and when they separate again.
    // Note that this is called from a job so whatever you do here needs to be thread safe.
    // Registering one is entirely optional.
    MyContactListener contact_listener;
    physics_system.SetContactListener(&contact_listener);

    // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
    // variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
    BodyInterface &body_interface = physics_system.GetBodyInterface();
}
```

## Step 4: Create Your First Objects

```cpp
void CreateObjects(BodyInterface &body_interface)
{
    // Create the ground
    {
        // Create the settings for the collision volume (the shape).
        // Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
        BoxShapeSettings ground_shape_settings(Vec3(100.0f, 1.0f, 100.0f));

        // Create the shape
        ShapeSettings::ShapeResult ground_shape_result = ground_shape_settings.Create();
        ShapeRefC ground_shape = ground_shape_result.Get(); // We don't expect an error here, but you can check ground_shape_result for errors

        // Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
        BodyCreationSettings ground_settings(ground_shape, RVec3(0.0_r, -1.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);

        // Create the actual body
        Body *ground = body_interface.CreateBody(ground_settings); // Note that if we run out of bodies this can return nullptr

        // Add it to the world
        body_interface.AddBody(ground->GetID(), EActivation::DontActivate);
    }

    // Create a sphere
    {
        // Create a sphere
        float sphere_radius = 0.5f;
        SphereShapeSettings sphere_shape_settings(sphere_radius);
        ShapeSettings::ShapeResult sphere_shape_result = sphere_shape_settings.Create();
        ShapeRefC sphere_shape = sphere_shape_result.Get();

        // Create the settings for the sphere body
        BodyCreationSettings sphere_settings(sphere_shape, RVec3(0.0_r, 2.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);

        // Create the sphere body
        BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

        // Now you can interact with the dynamic body, in this case we're going to give it a velocity.
        // (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
        body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));
    }
}
```

## Step 5: Run the Simulation

```cpp
void RunSimulation()
{
    // We need a temp allocator for temporary allocations during the physics update. We're
    // pre-allocating 10 MB to avoid having to do allocations during the physics update.
    // B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
    // If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
    // malloc / free.
    TempAllocatorImpl temp_allocator(10 * 1024 * 1024);

    // We need a job system that will execute physics jobs on multiple threads. Typically
    // you would implement the JobSystem interface yourself and let Jolt Physics run on top
    // of your own job scheduler. JobSystemThreadPool is an example implementation.
    JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

    // This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
    // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
    const uint cMaxBodies = 1024;

    // This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
    const uint cNumBodyMutexes = 0;

    // This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
    // body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
    // too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
    // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
    const uint cMaxBodyPairs = 1024;

    // This is the maximum size of the contact constraint buffer. If more contacts are detected than this number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
    // Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
    const uint cMaxContactConstraints = 1024;

    // Step the world
    const float deltaTime = 1.0f / 60.0f;
    for (int step = 0; step < 300; ++step)
    {
        // Next step
        physics_system.Update(deltaTime, 1, &job_system, &temp_allocator);

        // Optional: Output the position of the sphere
        RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
        cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << ")" << endl;
    }
}
```

## Complete Example

Here's a complete minimal example:

```cpp
#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <iostream>

using namespace JPH;
using namespace std;

int main()
{
    // Initialize Jolt
    RegisterDefaultAllocator();
    Factory::sInstance = new Factory();
    RegisterTypes();

    // Create physics system
    TempAllocatorImpl temp_allocator(10 * 1024 * 1024);
    JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

    // ... (layer definitions as above)

    PhysicsSystem physics_system;
    physics_system.Init(1024, 1024, 1024, broad_phase_layer_interface, 
                       object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

    BodyInterface &body_interface = physics_system.GetBodyInterface();

    // Create ground
    BoxShapeSettings ground_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
    ShapeRefC ground_shape = ground_shape_settings.Create().Get();
    BodyCreationSettings ground_settings(ground_shape, RVec3(0.0_r, -1.0_r, 0.0_r), 
                                        Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
    body_interface.CreateAndAddBody(ground_settings, EActivation::DontActivate);

    // Create sphere
    SphereShapeSettings sphere_shape_settings(0.5f);
    ShapeRefC sphere_shape = sphere_shape_settings.Create().Get();
    BodyCreationSettings sphere_settings(sphere_shape, RVec3(0.0_r, 2.0_r, 0.0_r), 
                                        Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
    BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

    // Simulate
    const float deltaTime = 1.0f / 60.0f;
    for (int step = 0; step < 60; ++step)
    {
        physics_system.Update(deltaTime, 1, &job_system, &temp_allocator);
        
        RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
        cout << "Step " << step << ": Y = " << position.GetY() << endl;
    }

    // Cleanup
    physics_system.UnregisterAllBodies();
    delete Factory::sInstance;
    UnregisterTypes();

    return 0;
}
```

## Next Steps

1. **Explore Shapes**: Try different shape types ([Shape Reference](bodies/shapes.md))
2. **Add Constraints**: Connect objects with joints ([Constraints Guide](constraints/README.md))
3. **Handle Collisions**: Implement contact listeners ([Collision Events](collision/events.md))
4. **Optimize Performance**: Learn about threading and optimization ([Performance Guide](performance.md))

## Common Issues

- **Assertion failures**: Make sure to call `RegisterTypes()` before creating any Jolt objects
- **Objects falling through ground**: Check collision layer configuration
- **Memory leaks**: Always call `UnregisterTypes()` and clean up Factory
- **Threading issues**: Use the correct BodyInterface for your threading model

## Reference Links

- [Complete API Reference](api-reference.md)
- [Core APIs](core/README.md)
- [Physics System](physics/README.md)
- [Bodies & Shapes](bodies/README.md)