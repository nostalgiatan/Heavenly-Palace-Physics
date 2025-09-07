// Heavenly Palace Physics - Physics Engine Plugin Registry Implementation
// SPDX-License-Identifier: MIT

#include "IPhysicsPlugin.h"
#include <map>
#include <vector>
#include <memory>
#include <mutex>

namespace HeavenlyPalace {

struct PluginRegistry::PluginEntry {
    PluginCreateFunc createFunc;
    std::unique_ptr<IPhysicsPlugin> instance;
    PluginInfo info;
    bool initialized = false;
};

struct RegistryImpl {
    std::map<PhysicsEngineType, PluginEntry> plugins;
    std::vector<PhysicsEngineType> availableEngines;
    std::mutex registryMutex;
    bool allPluginsInitialized = false;
};

PluginRegistry& PluginRegistry::GetInstance() {
    static PluginRegistry instance;
    return instance;
}

bool PluginRegistry::RegisterPlugin(PhysicsEngineType engineType, PluginCreateFunc createFunc) {
    if (!m_impl) {
        m_impl = std::make_unique<RegistryImpl>();
    }

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    // Check if plugin is already registered
    if (m_impl->plugins.find(engineType) != m_impl->plugins.end()) {
        return false; // Already registered
    }

    // Create a temporary instance to get plugin info
    auto tempPlugin = createFunc();
    if (!tempPlugin) {
        return false;
    }

    PluginEntry& entry = m_impl->plugins[engineType];
    entry.createFunc = createFunc;
    entry.info = tempPlugin->GetPluginInfo();
    entry.instance = std::move(tempPlugin);

    // Add to available engines list
    m_impl->availableEngines.push_back(engineType);

    return true;
}

void PluginRegistry::UnregisterPlugin(PhysicsEngineType engineType) {
    if (!m_impl) return;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    auto it = m_impl->plugins.find(engineType);
    if (it != m_impl->plugins.end()) {
        // Shutdown plugin if initialized
        if (it->second.initialized && it->second.instance) {
            it->second.instance->Shutdown();
        }
        
        m_impl->plugins.erase(it);
        
        // Remove from available engines list
        auto engineIt = std::find(m_impl->availableEngines.begin(), 
                                  m_impl->availableEngines.end(), engineType);
        if (engineIt != m_impl->availableEngines.end()) {
            m_impl->availableEngines.erase(engineIt);
        }
    }
}

std::unique_ptr<IPhysicsPlugin> PluginRegistry::CreatePlugin(PhysicsEngineType engineType) {
    if (!m_impl) return nullptr;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    auto it = m_impl->plugins.find(engineType);
    if (it == m_impl->plugins.end()) {
        return nullptr;
    }

    return it->second.createFunc();
}

const PhysicsEngineType* PluginRegistry::GetAvailableEngines(uint32_t& count) const {
    if (!m_impl) {
        count = 0;
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    count = static_cast<uint32_t>(m_impl->availableEngines.size());
    return m_impl->availableEngines.data();
}

bool PluginRegistry::IsEngineAvailable(PhysicsEngineType engineType) const {
    if (!m_impl) return false;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    return m_impl->plugins.find(engineType) != m_impl->plugins.end();
}

const PluginInfo* PluginRegistry::GetPluginInfo(PhysicsEngineType engineType) const {
    if (!m_impl) return nullptr;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    auto it = m_impl->plugins.find(engineType);
    if (it == m_impl->plugins.end()) {
        return nullptr;
    }

    return &it->second.info;
}

bool PluginRegistry::InitializeAllPlugins() {
    if (!m_impl) return true;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    if (m_impl->allPluginsInitialized) {
        return true;
    }

    bool allSucceeded = true;
    for (auto& [engineType, entry] : m_impl->plugins) {
        if (!entry.initialized && entry.instance) {
            if (entry.instance->IsCompatible()) {
                entry.initialized = entry.instance->Initialize();
                if (!entry.initialized) {
                    allSucceeded = false;
                }
            } else {
                // Mark as initialized but not supported
                entry.initialized = true;
                entry.info.isSupported = false;
            }
        }
    }

    m_impl->allPluginsInitialized = allSucceeded;
    return allSucceeded;
}

void PluginRegistry::ShutdownAllPlugins() {
    if (!m_impl) return;

    std::lock_guard<std::mutex> lock(m_impl->registryMutex);
    
    for (auto& [engineType, entry] : m_impl->plugins) {
        if (entry.initialized && entry.instance) {
            entry.instance->Shutdown();
            entry.initialized = false;
        }
    }
    
    m_impl->allPluginsInitialized = false;
}

} // namespace HeavenlyPalace