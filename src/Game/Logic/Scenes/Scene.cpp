#include "Game/Logic/Scenes.hpp"

namespace TR {
    void Scene::appendYAMLString(std::string str) {
        YAML::Node scene_YAML = YAML::LoadFile(getYAMLPath());
        const auto& Node = scene_YAML[str];

        if (Node["text"].IsDefined()) {
            appendGameTextString(Node["text"].as<std::string>());
            if (Node["action"].IsDefined()) {
                _state_data.current_prompt = Node["action"].as<std::string>();
            }
            return;
        }
        else if (Node["lines"].IsDefined()) {
            const auto& Node_Item = Node["lines"][getTextIndex()];
            appendGameTextString(Node_Item["text"].as<std::string>());
            if (Node_Item["action"].IsDefined()) {
                _state_data.current_prompt = Node_Item["action"].as<std::string>();
            }
            return;
        }
        appendGameTextString("Node Error");
    }

    void Scene::parsePromptAction() {
        if (!getDebugManager().isPromptShown()) {
            if (_state_data.current_prompt == "prompt_yn") {
                getDebugManager().showPrompt(PROMPT_YN);
            }
            else if (_state_data.current_prompt == "prompt_char") {
                getDebugManager().showPrompt(PROMPT_LIST_CHAR);
            }
            else if (_state_data.current_prompt == "prompt_market") {
                getDebugManager().showPrompt(_state_data.market_queue);
            }
            else if (_state_data.current_prompt == "prompt_land") {
                getDebugManager().showPrompt(PROMPT_LIST_LOT);
            }
            else if (_state_data.current_prompt == "display_mkt1") {
                if (_state_data.market_queue.empty()) {
                    for (const auto& market : gState.gMarket) {
                        if (market["tier"].as<int>() == 1) {
                            std::string market_str = (market)["id_name"].as<std::string>();
                            _state_data.market_queue.push_back(market_str);

                            appendGameTextString("\n");
                            appendGameTextString(market["name"].as<std::string>());
                        }
                    }
                }
            }
            else {
                getDebugManager().hidePrompt();
            }
        }
    }

	void Scene::substitutePlaceholder() {
        bool isPlaceholder = false;
        std::string new_string, placeholder;
		for (const auto& character : _state_data.current_text_string) {
            if (isPlaceholder) {
                if (character == '}') {
                    new_string += TEXT_TEMP_VALUE.at(placeholder);
                    placeholder.clear();
                    isPlaceholder = false;
                    continue;
                }
                placeholder += character;
            }
            else {
                if (character == '{') {
                    isPlaceholder = true;
                    continue;
                }
                new_string += character;
            }
		}
        _state_data.current_text_string = new_string;
	}
}