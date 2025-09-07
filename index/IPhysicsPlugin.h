// Heavenly Palace Physics - Physics Engine Plugin Interface
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <functional>

namespace HeavenlyPalace {

// Forward declarations
class IPhysicsSystem;

/// Plugin information structure
struct PluginInfo {
    std::string name;               ///< Human-readable name of the plugin
    std::string version;            ///< Plugin version string
    std::string description;        ///< Brief description of the plugin
    PhysicsEngineType engineType;  ///< Engine type this plugin provides
    std::string author;             ///< Plugin author/organization
    uint32_t apiVersion;            ///< API version this plugin was built for
    bool isSupported;               ///< Whether this plugin is supported on current platform
};

/// Abstract interface for physics engine plugins
class IPhysicsPlugin {
public:
    virtual ~IPhysicsPlugin() = default;

    /// Get plugin information
    /// @return Plugin information structure
    virtual const PluginInfo& GetPluginInfo() const = 0;

    /// Check if this plugin is compatible with the current system
    /// @return True if compatible, false otherwise
    virtual bool IsCompatible() const = 0;

    /// Create a physics system instance
    /// @return New physics system instance, nullptr if creation failed
    virtual std::unique_ptr<IPhysicsSystem> CreatePhysicsSystem() = 0;

    /// Initialize the plugin (called once when plugin is loaded)
    /// @return True if initialization succeeded
    virtual bool Initialize() = 0;

    /// Shutdown the plugin (called once when plugin is unloaded)
    virtual void Shutdown() = 0;

    /// Get additional features supported by this plugin
    /// @return Bitmask of supported features
    virtual uint32_t GetSupportedFeatures() const = 0;
};

/// Plugin feature flags
enum class PluginFeature : uint32_t {
    SoftBodies         = 1 << 0,  ///< Soft body simulation
    FluidSimulation    = 1 << 1,  ///< Fluid/particle simulation  
    CharacterControl   = 1 << 2,  ///< Character controller
    VehicleSimulation  = 1 << 3,  ///< Vehicle physics
    ClothSimulation    = 1 << 4,  ///< Cloth simulation
    DestructibleBodies = 1 << 5,  ///< Destructible objects
    ContinuousCD       = 1 << 6,  ///< Continuous collision detection
    Deterministic      = 1 << 7,  ///< Deterministic simulation
    DoublePrecision    = 1 << 8,  ///< Double precision math
    Multithreading     = 1 << 9,  ///< Multi-threaded simulation
    GPU_Acceleration   = 1 << 10, ///< GPU acceleration
    PBD_Solver         = 1 << 11  ///< Position-based dynamics solver
};

/// Plugin factory function type
using PluginCreateFunc = std::function<std::unique_ptr<IPhysicsPlugin>()>;

/// Plugin registration helper class
class PluginRegistry {
public:
    /// Get the global plugin registry instance
    static PluginRegistry& GetInstance();

    /// Register a physics engine plugin
    /// @param engineType Engine type this plugin provides
    /// @param createFunc Factory function to create plugin instances
    /// @return True if registration succeeded
    bool RegisterPlugin(PhysicsEngineType engineType, PluginCreateFunc createFunc);

    /// Unregister a plugin
    /// @param engineType Engine type to unregister
    void UnregisterPlugin(PhysicsEngineType engineType);

    /// Create a plugin instance for the specified engine type
    /// @param engineType Engine type to create
    /// @return Plugin instance or nullptr if not available
    std::unique_ptr<IPhysicsPlugin> CreatePlugin(PhysicsEngineType engineType);

    /// Get list of available engine types
    /// @param count Output parameter for number of engines
    /// @return Array of available engine types
    const PhysicsEngineType* GetAvailableEngines(uint32_t& count) const;

    /// Check if an engine type is available
    /// @param engineType Engine type to check
    /// @return True if available, false otherwise
    bool IsEngineAvailable(PhysicsEngineType engineType) const;

    /// Get plugin information for an engine type
    /// @param engineType Engine type to query
    /// @return Plugin info or nullptr if not available
    const PluginInfo* GetPluginInfo(PhysicsEngineType engineType) const;

    /// Initialize all registered plugins
    /// @return True if all plugins initialized successfully
    bool InitializeAllPlugins();

    /// Shutdown all plugins
    void ShutdownAllPlugins();

private:
    PluginRegistry() = default;
    struct PluginEntry;
    std::unique_ptr<struct RegistryImpl> m_impl;
};

/// Automatic plugin registration helper macro
#define REGISTER_PHYSICS_PLUGIN(ENGINE_TYPE, PLUGIN_CLASS) \
    namespace { \
        struct AutoRegister##PLUGIN_CLASS { \
            AutoRegister##PLUGIN_CLASS() { \
                PluginRegistry::GetInstance().RegisterPlugin( \
                    ENGINE_TYPE, \
                    []() -> std::unique_ptr<IPhysicsPlugin> { \
                        return std::make_unique<PLUGIN_CLASS>(); \
                    } \
                ); \
            } \
        }; \
        static AutoRegister##PLUGIN_CLASS s_autoRegister##PLUGIN_CLASS; \
    }

/// Physics engine capabilities structure for detailed feature queries
struct EngineCapabilities {
    bool supportsMultithreading = false;
    bool supportsSoftBodies = false;
    bool supportsContinuousCD = false;
    bool supportsDeterministic = false;
    bool supportsGPUAcceleration = false;
    bool supportsDoublePrecision = false;
    uint32_t maxBodies = 0;           ///< Maximum number of bodies (0 = unlimited)
    uint32_t maxConstraints = 0;      ///< Maximum number of constraints (0 = unlimited)
    float minTimeStep = 0.0f;         ///< Minimum simulation time step
    float maxTimeStep = 0.0f;         ///< Maximum simulation time step
    std::string platformRequirements; ///< Platform-specific requirements
};

/// Extended plugin interface for advanced features
class IAdvancedPhysicsPlugin : public IPhysicsPlugin {
public:
    /// Get detailed engine capabilities
    /// @return Engine capabilities structure
    virtual const EngineCapabilities& GetCapabilities() const = 0;

    /// Check if a specific feature combination is supported
    /// @param features Bitmask of features to check
    /// @return True if all features are supported
    virtual bool SupportsFeatureCombination(uint32_t features) const = 0;

    /// Get recommended settings for optimal performance
    /// @param bodyCount Expected number of bodies
    /// @param constraintCount Expected number of constraints
    /// @return Recommended configuration settings as key-value pairs
    virtual std::map<std::string, std::string> GetRecommendedSettings(
        uint32_t bodyCount, uint32_t constraintCount) const = 0;
};

} // namespace HeavenlyPalace