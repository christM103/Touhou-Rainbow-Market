#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Engine {
	struct DebugComponent {
        static inline int _debug_active = 0;
		static inline std::string _current_text = "";
        static inline std::string _prompt_text = "";

        static inline uint8_t _text_index = 0;
        static inline bool _prompt_active = false;
        static inline std::vector<std::string> _prompt_strings;
        static inline uint8_t _prompt_index = 0;

        static inline void debugPrint(const std::string str) {
            if (_current_text != str) {
                _current_text = str;
            }
        }

        static inline void resetIndex() {
            _text_index = 0;
        }

        static inline void enablePrompt(const std::vector<std::string> str_vector) {
            if (!_prompt_active) {
                _prompt_active = true;
                for (auto& str : str_vector) {
                    _prompt_strings.push_back(str);
                }
            }
        }

        static inline void disablePrompt() {
            if (_prompt_active) {
                _prompt_active = false;
                _prompt_text.clear();
                _prompt_strings.clear();
                _prompt_index = 0;
            }
        }
	};
}