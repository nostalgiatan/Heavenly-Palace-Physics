// Heavenly Palace Physics - Universal Physics Engine Abstraction
// SPDX-License-Identifier: MIT

#include "HeavenlyPalacePhysics.h"
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
    static const std::array<PhysicsEngineType, 1> supportedEngines = {
        PhysicsEngineType::Jolt
        // PhysicsEngineType::Bullet,  // Future support
        // PhysicsEngineType::PhysX,   // Future support
        // PhysicsEngineType::Box2D    // Future support
    };
    
    count = static_cast<uint32_t>(supportedEngines.size());
    return supportedEngines.data();
}

bool IsEngineSupported(PhysicsEngineType engineType) {
    uint32_t count;
    const PhysicsEngineType* engines = GetSupportedEngines(count);
    
    for (uint32_t i = 0; i < count; ++i) {
        if (engines[i] == engineType) {
            return true;
        }
    }
    
    return false;
}

} // namespace HeavenlyPalace