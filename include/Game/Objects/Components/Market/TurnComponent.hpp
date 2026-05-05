#pragma once

#include <type_traits>
#include <vector>

namespace TR {
	struct TurnsComponent {
		struct TurnFlags {
			bool turn_started{ false };
			bool turn_ended{ false };
			bool event_turn_start{ false };
			bool event_turn_mid{ false };
		};

		uint8_t current_turn{ 1 };
		uint8_t max_turns;
		std::map<uint8_t, TurnFlags> turns;

		TurnsComponent(uint8_t t = 5) : max_turns(t) {
			for (auto i = 1; i <= max_turns; i++) {
				turns.emplace(i, TurnFlags());
			}
		}
	};

	struct TimerComponent {
		bool timer_active{ false };
		uint32_t time{ 0 }; // In miliseconds
	};
}