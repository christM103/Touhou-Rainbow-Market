#pragma once

#include <type_traits>
#include <functional>

#include <SDL2/SDL_Timer.h>

namespace Engine {
	class Timer {
	public:

		enum Time_Units : uint32_t {
			MILLISECONDS = 1, 
			SECONDS = 1000, 
			MINUTES = 60000,
			HOURS = 3600000
		};


		/// -- Constructor & Destructor -- ///

		Timer(bool initial);
		~Timer();


		/// -- Utility Functions -- ///

		/// @brief Resumes the timer if the timer was not already active
		/// @return True if it was paused previously, False if there was no change
		bool const resumeTimer();

		/// @brief Resets the timer
		/// @return True if succesfully reset, False if there was no change
		bool const resetTimer();

		/// @brief Paused the timer if the timer was not already pauseed
		/// @return True if it was active previously, False if there was no change
		bool const pauseTimer();

		/// @brief Set the timer delay
		/// @param time The new time delay
		/// @param units The units of the mesurement (seconds in default)
		void const setDelay(uint32_t time, Time_Units units = SECONDS);


		/// @brief Callback function used to control ticks
		static Uint32 callback(Uint32 delay, void* ptr);

	private:
		uint32_t _current_time{ 0 }, _current_delay{ 500 };
		SDL_TimerID _timer;
		bool _active, _secondTick{ false }, _minuteTick{ false };
	};
}