// Heavenly Palace Physics - Physics Engine Plugin Interface
// SPDX-License-Identifier: MIT
#pragma once

#include "Common.h"
#include <memory>
#include <map>
#include <functional>

namespace HeavenlyPalace {

// Forward declarations
class IPhysicsSystem;

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

/// Plugin factory function type
using PluginCreateFunc = std::function<std::unique_ptr<IPhysicsPlugin>()>;

/// Plugin registry for managing physics engine plugins
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

} // namespace HeavenlyPalace