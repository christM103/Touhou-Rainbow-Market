#include "Engine/Core/Debugger.hpp"

namespace Engine {

DebugManager& DebugManager::instance() {
    static DebugManager inst;
    return inst;
}

}