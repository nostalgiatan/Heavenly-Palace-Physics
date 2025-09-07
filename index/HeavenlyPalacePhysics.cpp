// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT

#include "HeavenlyPalacePhysics.h"
#include "IPhysicsPlugin.h"
#include <array>
#include <cstdio>

namespace HeavenlyPalace {

const char* GetVersionString() {
    static char versionString[32];
    snprintf(versionString, sizeof(versionString), "%d.%d.%d", 
             VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    return versionString;
}

const PhysicsEngineType* GetSupportedEngines(uint32_t& count) {
    // Use plugin registry for dynamic engine discovery
    return PluginRegistry::GetInstance().GetAvailableEngines(count);
}

bool IsEngineSupported(PhysicsEngineType engineType) {
    return PluginRegistry::GetInstance().IsEngineAvailable(engineType);
}

// PhysicsManager implementation
std::unique_ptr<IPhysicsSystem> PhysicsManager::s_instance;
PhysicsEngineType PhysicsManager::s_currentEngineType = PhysicsEngineType::Jolt;
bool PhysicsManager::s_pluginsInitialized = false;

IPhysicsSystem* PhysicsManager::GetInstance() {
    return s_instance.get();
}

bool PhysicsManager::CreateSystem(PhysicsEngineType engineType) {
    // Ensure plugins are initialized
    if (!s_pluginsInitialized) {
        if (!InitializePlugins()) {
            return false;
        }
    }

    // Destroy existing system if any
    DestroySystem();

    // Create plugin instance
    auto currentPlugin = PluginRegistry::GetInstance().CreatePlugin(engineType);
    if (!currentPlugin) {
        return false;
    }

    // Create physics system from plugin
    s_instance = currentPlugin->CreatePhysicsSystem();
    if (!s_instance) {
        return false;
    }

    // Initialize the physics system
    if (!s_instance->Initialize(engineType)) {
        s_instance.reset();
        return false;
    }

    s_currentEngineType = engineType;
    return true;
}

void PhysicsManager::DestroySystem() {
    if (s_instance) {
        s_instance->Shutdown();
        s_instance.reset();
    }
}

bool PhysicsManager::IsReady() {
    return s_instance && s_instance->IsInitialized();
}

const PhysicsEngineType* PhysicsManager::GetAvailableEngines(uint32_t& count) {
    return PluginRegistry::GetInstance().GetAvailableEngines(count);
}

const PluginInfo* PhysicsManager::GetEngineInfo(PhysicsEngineType engineType) {
    return PluginRegistry::GetInstance().GetPluginInfo(engineType);
}

bool PhysicsManager::SwitchEngine(PhysicsEngineType engineType, bool preserveState) {
    if (s_currentEngineType == engineType && IsReady()) {
        return true; // Already using this engine
    }

    // For now, we don't support state preservation - would be a complex feature
    // This could be implemented in the future by serializing world state
    if (preserveState) {
        // TODO: Implement state preservation
        // 1. Serialize current world state
        // 2. Create new system
        // 3. Deserialize world state into new system
    }

    return CreateSystem(engineType);
}

bool PhysicsManager::InitializePlugins() {
    if (s_pluginsInitialized) {
        return true;
    }

    s_pluginsInitialized = PluginRegistry::GetInstance().InitializeAllPlugins();
    return s_pluginsInitialized;
}

void PhysicsManager::ShutdownPlugins() {
    DestroySystem();
    PluginRegistry::GetInstance().ShutdownAllPlugins();
    s_pluginsInitialized = false;
}

bool PhysicsManager::IsEngineSupported(PhysicsEngineType engineType) {
    const PluginInfo* info = GetEngineInfo(engineType);
    return info && info->isSupported;
}

} // namespace HeavenlyPalace