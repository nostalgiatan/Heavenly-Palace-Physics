// Heavenly Palace Physics - Box2D Plugin Implementation
// SPDX-License-Identifier: MIT

#include "../IPhysicsPlugin.h"
#include "Box2DPhysicsSystem.h"

namespace HeavenlyPalace {

/// Box2D Physics Engine Plugin
class Box2DPhysicsPlugin : public IPhysicsPlugin {
public:
    Box2DPhysicsPlugin() {
        m_pluginInfo.name = "Box2D Physics Engine";
        m_pluginInfo.version = "2.4.1";
        m_pluginInfo.description = "2D physics engine with high performance and stability";
        m_pluginInfo.engineType = PhysicsEngineType::Box2D;
        m_pluginInfo.author = "Erin Catto / Box2D Team";
        m_pluginInfo.apiVersion = 1;
        m_pluginInfo.isSupported = true;
    }

    const PluginInfo& GetPluginInfo() const override {
        return m_pluginInfo;
    }

    bool IsCompatible() const override {
        // Box2D should be compatible on all platforms where it can be built
        return true;
    }

    std::unique_ptr<IPhysicsSystem> CreatePhysicsSystem() override {
        return std::make_unique<Box2DPhysicsSystem>();
    }

    bool Initialize() override {
        // Box2D doesn't require global initialization
        m_initialized = true;
        return true;
    }

    void Shutdown() override {
        // Box2D doesn't require global cleanup
        m_initialized = false;
    }

    uint32_t GetSupportedFeatures() const override {
        return static_cast<uint32_t>(PluginFeature::ContinuousCD) |
               static_cast<uint32_t>(PluginFeature::Deterministic);
    }

private:
    PluginInfo m_pluginInfo;
    bool m_initialized = false;
};

// Register the Box2D plugin automatically
REGISTER_PHYSICS_PLUGIN(PhysicsEngineType::Box2D, Box2DPhysicsPlugin);

} // namespace HeavenlyPalace