# Core APIs

Core infrastructure APIs that provide the foundation for the Jolt Physics Engine. These include memory management, job systems, object factories, and basic utilities.

## Essential Core Classes

### System Management
- **Factory** - Object creation and type registration system
- **JobSystem** - Multi-threaded job execution framework
  - **JobSystemThreadPool** - Thread pool-based job system
  - **JobSystemSingleThreaded** - Single-threaded job system for debugging
  - **JobSystemWithBarrier** - Job system with synchronization barriers

### Memory Management
- **Memory** - Global memory allocation functions
- **TempAllocator** - Fast temporary memory allocator
- **STLAllocator** - STL-compatible allocator
- **STLTempAllocator** - STL-compatible temporary allocator

### Object Model
- **RTTI** - Runtime type information system
- **Reference** - Reference counting base class
- **RefTarget** - Base class for reference-counted objects
- **NonCopyable** - Base class for non-copyable objects

### Utilities
- **Profiler** - Performance profiling utilities
- **Semaphore** - Thread synchronization primitive
- **Array** - Dynamic array container
- **HashTable** - Hash table container

## Core Classes by Category

### Job System (4 classes)
```cpp
// Basic usage
JobSystemThreadPool job_system(max_jobs, max_barriers, num_threads);
```

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| `JobSystem` | Abstract base for job execution | `QueueJob()`, `CreateBarrier()` |
| `JobSystemThreadPool` | Multi-threaded job executor | `Init()`, `GetMaxConcurrency()` |
| `JobSystemSingleThreaded` | Single-threaded debug version | `ProcessNextJob()` |
| `JobSystemWithBarrier` | Job system with barriers | `WaitForBarrier()` |

### Memory Management (8 classes)
```cpp
// Allocator usage
TempAllocator temp_allocator(1024 * 1024);
Array<Vec3> vertices(&temp_allocator);
```

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| `TempAllocator` | Fast temporary allocation | `Allocate()`, `Free()` |
| `STLAllocator` | STL-compatible allocator | `allocate()`, `deallocate()` |
| `FixedSizeFreeList` | Fixed-size block allocator | `ConstructObject()`, `DestructObject()` |

### Object Model (6 classes)
```cpp
// Reference counting
Ref<Shape> shape = new BoxShape(Vec3(1, 1, 1));
```

| Class | Purpose | Key Methods |
|-------|---------|-------------|
| `RTTI` | Runtime type information | `GetName()`, `GetHash()` |
| `Factory` | Object creation system | `CreateObject()`, `Register()` |
| `RefTarget` | Reference counting base | `AddRef()`, `Release()` |

## Usage Patterns

### Initialization
```cpp
// Initialize core systems
RegisterDefaultAllocator();
Factory::sInstance = new Factory();

// Register types
RegisterTypes();

// Setup job system
JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
```

### Memory Management
```cpp
// Use temporary allocator for short-lived objects
TempAllocatorImpl temp_allocator(10 * 1024 * 1024);

// Create arrays with custom allocator
Array<BodyCreationSettings> bodies(&temp_allocator);
```

### Job System
```cpp
// Queue a job
class MyJob : public Job
{
public:
    virtual void Execute() override { /* work */ }
};

JobHandle handle = job_system.CreateJob("MyJob", Color::sRed, new MyJob());
job_system.QueueJob(handle);
```

## Best Practices

1. **Always initialize Factory and register types** before using any Jolt objects
2. **Use TempAllocator** for short-lived collections and temporary data
3. **Configure JobSystem** based on available CPU cores
4. **Use reference counting** (Ref<>) for shared objects like Shapes
5. **Call RegisterDefaultAllocator()** early in your application

## Related Documentation
- [Physics System Setup](../physics/getting-started.md)
- [Memory Management Guide](memory-management.md)
- [Job System Tutorial](job-system.md)
- [Type Registration](type-registration.md)