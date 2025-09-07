# Constraints System

Constraints connect bodies together and limit their relative motion. Jolt Physics provides various constraint types for different joint behaviors.

## Constraint Types

### Basic Constraints
- **FixedConstraint** - Weld two bodies together (no relative motion)
- **PointConstraint** - Ball and socket joint (rotation allowed)
- **DistanceConstraint** - Maintains distance between two points

### Rotational Constraints  
- **HingeConstraint** - Single axis rotation (door hinge)
- **SliderConstraint** - Single axis translation (piston)
- **ConeConstraint** - Limits rotation to within a cone

### Advanced Constraints
- **SwingTwistConstraint** - Shoulder-like joint with swing and twist limits
- **SixDOFConstraint** - Full control over all 6 degrees of freedom
- **PathConstraint** - Constrains motion along a predefined path

## Basic Usage

### Fixed Constraint (Weld)
```cpp
// Create two bodies that should be welded together
BodyID body1 = CreateBox(RVec3(0, 5, 0));
BodyID body2 = CreateBox(RVec3(2, 5, 0));

// Create fixed constraint
FixedConstraintSettings fixed_settings;
fixed_settings.mSpace = EConstraintSpace::WorldSpace;
fixed_settings.mPoint1 = RVec3(1, 5, 0);  // Connection point in world space
fixed_settings.mPoint2 = RVec3(1, 5, 0);

FixedConstraint* constraint = new FixedConstraint(*body1, *body2, fixed_settings);
physics_system.AddConstraint(constraint);
```

### Hinge Constraint
```cpp
// Create hinge joint (door-like rotation)
HingeConstraintSettings hinge_settings;
hinge_settings.mSpace = EConstraintSpace::WorldSpace;
hinge_settings.mPoint1 = RVec3(0, 5, 0);     // Hinge point
hinge_settings.mPoint2 = RVec3(0, 5, 0);
hinge_settings.mHingeAxis1 = Vec3(0, 1, 0);  // Y-axis rotation
hinge_settings.mHingeAxis2 = Vec3(0, 1, 0);

// Optional: Add limits
hinge_settings.mLimitsMin = -JPH_PI / 2;     // -90 degrees
hinge_settings.mLimitsMax = JPH_PI / 2;      // +90 degrees

HingeConstraint* hinge = new HingeConstraint(*body1, *body2, hinge_settings);
physics_system.AddConstraint(hinge);
```

### Distance Constraint (Spring)
```cpp
// Create spring between two bodies
DistanceConstraintSettings spring_settings;
spring_settings.mSpace = EConstraintSpace::WorldSpace;
spring_settings.mPoint1 = body_interface.GetPosition(body1);
spring_settings.mPoint2 = body_interface.GetPosition(body2);

// Spring settings
spring_settings.mMinDistance = 1.0f;        // Minimum distance
spring_settings.mMaxDistance = 3.0f;        // Maximum distance
spring_settings.mLimitsSpringSettings.mFrequency = 2.0f;  // Spring frequency
spring_settings.mLimitsSpringSettings.mDamping = 0.5f;    // Damping

DistanceConstraint* spring = new DistanceConstraint(*body1, *body2, spring_settings);
physics_system.AddConstraint(spring);
```

## Motors and Limits

### Motor Settings
```cpp
// Add motor to hinge constraint
MotorSettings motor_settings;
motor_settings.mFrequency = 4.0f;           // Motor frequency
motor_settings.mDamping = 1.0f;             // Motor damping

hinge_settings.mMotorSettings = motor_settings;

// Control motor during simulation
HingeConstraint* hinge_constraint = /* ... */;
hinge_constraint->SetMotorState(EMotorState::Velocity);
hinge_constraint->SetTargetAngularVelocity(1.0f);  // 1 rad/s
```

### Limits and Springs
```cpp
// Add soft limits with springs
SpringSettings spring_settings;
spring_settings.mFrequency = 10.0f;         // Spring stiffness
spring_settings.mDamping = 0.8f;            // Spring damping

hinge_settings.mLimitsSpringSettings = spring_settings;
hinge_settings.mLimitsMin = -JPH_PI;        // Lower limit
hinge_settings.mLimitsMax = JPH_PI;         // Upper limit
```

## Advanced Constraints

### Six DOF Constraint
```cpp
// Full control over all 6 degrees of freedom
SixDOFConstraintSettings sixdof_settings;
sixdof_settings.mSpace = EConstraintSpace::LocalToBodyCOM;
sixdof_settings.mPosition1 = Vec3(0, 0, 0);
sixdof_settings.mPosition2 = Vec3(0, 0, 0);

// Configure each axis
sixdof_settings.mAxisX1 = Vec3(1, 0, 0);
sixdof_settings.mAxisY1 = Vec3(0, 1, 0);
sixdof_settings.mAxisX2 = Vec3(1, 0, 0);
sixdof_settings.mAxisY2 = Vec3(0, 1, 0);

// Set limits for translation
sixdof_settings.SetLimitedAxis(SixDOFConstraintSettings::EAxis::TranslationX, -1.0f, 1.0f);
sixdof_settings.SetLimitedAxis(SixDOFConstraintSettings::EAxis::TranslationY, -2.0f, 2.0f);
sixdof_settings.SetFreeAxis(SixDOFConstraintSettings::EAxis::TranslationZ);

// Set limits for rotation  
sixdof_settings.SetLimitedAxis(SixDOFConstraintSettings::EAxis::RotationX, -JPH_PI/4, JPH_PI/4);

SixDOFConstraint* sixdof = new SixDOFConstraint(*body1, *body2, sixdof_settings);
physics_system.AddConstraint(sixdof);
```

### Swing Twist Constraint
```cpp
// Shoulder-like joint
SwingTwistConstraintSettings shoulder_settings;
shoulder_settings.mSpace = EConstraintSpace::LocalToBodyCOM;
shoulder_settings.mPosition1 = Vec3(0, 0, 0);
shoulder_settings.mPosition2 = Vec3(0, 0, 0);
shoulder_settings.mTwistAxis1 = Vec3(1, 0, 0);  // Primary rotation axis
shoulder_settings.mTwistAxis2 = Vec3(1, 0, 0);
shoulder_settings.mPlaneAxis1 = Vec3(0, 1, 0);  // Swing plane
shoulder_settings.mPlaneAxis2 = Vec3(0, 1, 0);

// Set swing limits (cone)
shoulder_settings.mNormalHalfConeAngle = JPH_PI / 6;    // 30 degree cone
shoulder_settings.mPlaneHalfConeAngle = JPH_PI / 4;     // 45 degree cone

// Set twist limits
shoulder_settings.mTwistMinAngle = -JPH_PI / 3;         // -60 degrees
shoulder_settings.mTwistMaxAngle = JPH_PI / 3;          // +60 degrees

SwingTwistConstraint* shoulder = new SwingTwistConstraint(*body1, *body2, shoulder_settings);
physics_system.AddConstraint(shoulder);
```

## Constraint Management

### Adding and Removing Constraints
```cpp
// Add constraint to physics system
Constraint* constraint = new HingeConstraint(*body1, *body2, hinge_settings);
physics_system.AddConstraint(constraint);

// Remove constraint
physics_system.RemoveConstraint(constraint);
```

### Breaking Constraints
```cpp
// Set breaking threshold
constraint_settings.mDrawConstraintSize = 1.0f;

// Check if constraint should break during simulation
class BreakingConstraintListener : public PhysicsStepListener
{
public:
    virtual void OnStep(float inDeltaTime, PhysicsSystem* inPhysicsSystem) override
    {
        for (Constraint* constraint : constraints_to_check)
        {
            float applied_force = constraint->GetTotalLambdaPosition().Length();
            if (applied_force > breaking_threshold)
            {
                inPhysicsSystem->RemoveConstraint(constraint);
                // Handle constraint breaking...
            }
        }
    }
};
```

## Constraint Coordinate Systems

### World Space
```cpp
// Points and axes specified in world coordinates
settings.mSpace = EConstraintSpace::WorldSpace;
settings.mPoint1 = RVec3(1, 2, 3);  // World position
settings.mHingeAxis1 = Vec3(0, 1, 0);  // World Y-axis
```

### Local to Body Center of Mass
```cpp
// Points and axes relative to body center of mass
settings.mSpace = EConstraintSpace::LocalToBodyCOM;
settings.mPosition1 = Vec3(0.5, 0, 0);  // 0.5m to the right of COM
```

### Local to Body Origin
```cpp
// Points and axes relative to body origin
settings.mSpace = EConstraintSpace::LocalToBodyOrigin;
settings.mPosition1 = Vec3(0, 1, 0);  // 1m above body origin
```

## Complete Ragdoll Example

```cpp
void CreateSimpleRagdoll(BodyInterface& body_interface, PhysicsSystem& physics_system)
{
    // Create body parts
    BodyID head = CreateSphere(RVec3(0, 7, 0), 0.3f);
    BodyID torso = CreateBox(RVec3(0, 5, 0), Vec3(0.4f, 0.8f, 0.2f));
    BodyID upper_arm = CreateCapsule(RVec3(-1, 6, 0), 0.8f, 0.1f);
    BodyID lower_arm = CreateCapsule(RVec3(-2.5, 6, 0), 0.7f, 0.09f);

    // Connect head to torso (ball joint)
    PointConstraintSettings neck_settings;
    neck_settings.mSpace = EConstraintSpace::WorldSpace;
    neck_settings.mPoint1 = RVec3(0, 6.5, 0);
    neck_settings.mPoint2 = RVec3(0, 6.5, 0);
    physics_system.AddConstraint(new PointConstraint(*GetBody(head), *GetBody(torso), neck_settings));

    // Connect upper arm to torso (shoulder joint)
    SwingTwistConstraintSettings shoulder_settings;
    shoulder_settings.mSpace = EConstraintSpace::WorldSpace;
    shoulder_settings.mPosition1 = RVec3(-0.4, 6, 0);
    shoulder_settings.mPosition2 = RVec3(-0.4, 6, 0);
    shoulder_settings.mTwistAxis1 = Vec3(-1, 0, 0);
    shoulder_settings.mTwistAxis2 = Vec3(1, 0, 0);
    shoulder_settings.mPlaneAxis1 = Vec3(0, 1, 0);
    shoulder_settings.mPlaneAxis2 = Vec3(0, 1, 0);
    shoulder_settings.mNormalHalfConeAngle = JPH_PI / 3;  // 60 degree cone
    physics_system.AddConstraint(new SwingTwistConstraint(*GetBody(upper_arm), *GetBody(torso), shoulder_settings));

    // Connect lower arm to upper arm (elbow joint)
    HingeConstraintSettings elbow_settings;
    elbow_settings.mSpace = EConstraintSpace::WorldSpace;
    elbow_settings.mPoint1 = RVec3(-1.8, 6, 0);
    elbow_settings.mPoint2 = RVec3(-1.8, 6, 0);
    elbow_settings.mHingeAxis1 = Vec3(0, 0, 1);  // Z-axis rotation
    elbow_settings.mHingeAxis2 = Vec3(0, 0, 1);
    elbow_settings.mLimitsMin = 0;               // No extension past straight
    elbow_settings.mLimitsMax = 2.5f;            // Can bend 143 degrees
    physics_system.AddConstraint(new HingeConstraint(*GetBody(lower_arm), *GetBody(upper_arm), elbow_settings));
}
```

## Best Practices

1. **Choose appropriate constraint types** - Use the simplest constraint that provides the needed behavior
2. **Set reasonable limits** - Avoid extreme limit values that can cause instability  
3. **Use motors sparingly** - Motors can cause instability if not tuned properly
4. **Consider breaking constraints** - Allow constraints to break under excessive force for realistic behavior
5. **Test constraint hierarchies** - Complex constraint chains can be unstable
6. **Use local coordinate spaces** - Often more intuitive than world space

## Related Documentation
- [Bodies & Shapes](../bodies/README.md)
- [Physics System](../physics/README.md) 
- [Ragdoll Tutorial](ragdoll-tutorial.md)
- [Motor Control Guide](motor-control.md)