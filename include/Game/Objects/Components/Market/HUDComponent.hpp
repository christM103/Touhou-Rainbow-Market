#pragma once

#include <cstdint>

namespace TR{
	struct HUDComponent {
		enum HUDFlags : uint16_t {
			Null = 0,
			Show_Portrait = 0 << 1,
			Show_Profits = 1 << 1,
			Show_Power = 2 << 1,
			Show_Market_Info = 3 << 1,
			Show_Timer = 4 << 1,

			Show_All = 23,
		};

		bool interative{ false };
		HUDFlags hudFlags{ HUDFlags::Show_All };
	};
}