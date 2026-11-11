#include "Game/Logic/Common.hpp"

namespace TR {
	struct ActionComponent {
		Action_ID action_id{ Action_ID::A_NULL };
		Action_States action_state{ Action_States::Null };
		Player_ID target_player{ Player_ID::Player_Null };
		std::array<Action_Type, 4> action_type;
		std::array<Land_ID, 16> target_land;
	};
}