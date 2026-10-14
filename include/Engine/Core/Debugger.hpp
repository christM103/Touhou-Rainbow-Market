#pragma once

#include <string>
#include <vector>

#include "Engine/ECS/Components/DebugComponent.hpp"

namespace Engine {
    class DebugManager {
    public:
        DebugManager() = default;
        ~DebugManager() = default;

        static DebugManager& instance();

        inline void setEnabled(bool enabled) { _debug_enabled = enabled; }
        inline bool isEnabled() const { return _debug_enabled; }

        inline void displayText(const std::string& text) const {
            if (_debug_enabled) {
                DebugComponent::debugPrint(text);
            }
        }
        inline void clearText() const {
            if (_debug_enabled) {
                DebugComponent::debugPrint("");
            }
        }

        inline void showPrompt(const std::vector<std::string>& options) const {
            if (_debug_enabled) {
                DebugComponent::enablePrompt(options);
            }
        }
        inline void hidePrompt() const {
            if (_debug_enabled) {
                DebugComponent::disablePrompt();
            }
        }
        inline bool isPromptShown() const {
            return _debug_enabled && DebugComponent::_prompt_active;
        };

        inline uint8_t getSelectedPromptIndex() const {
            if (_debug_enabled && DebugComponent::_prompt_active) {
                return DebugComponent::_prompt_index;
            }

            return 0;
        }
        inline void resetPromptIndex() const {
            if (_debug_enabled) {
                DebugComponent::_prompt_index = 0;
            }
        }

    private:
        bool _debug_enabled = true;
    };
}