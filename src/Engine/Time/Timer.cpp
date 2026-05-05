#pragma once

#include "Engine/Time/Timer.hpp"



Engine::Timer::Timer(bool initial) : _timer(SDL_AddTimer(500, callback, this)), _active(initial) {}

Engine::Timer::~Timer() {
	SDL_RemoveTimer(_timer);
}

bool const Engine::Timer::resumeTimer() {
	if (!_active) {
		_active = true;
		return true;
	}
	return false;
}

bool const Engine::Timer::resetTimer() {
	if (_current_time == 0) {
		return false;
	}
	_current_time = 0;
	return true;
}

bool const Engine::Timer::pauseTimer() {
	if (_active) {
		_active = false;
		return true;
	}
	return false;
}

void const Engine::Timer::setDelay(uint32_t time, Time_Units units) {
	_current_delay = time * units;
}

// Utility Functions

Uint32 Engine::Timer::callback(Uint32 delay, void* ptr) {
	Timer* timer = static_cast<Timer*>(ptr);
	if (timer->_active && timer->_current_time % Time_Units::MINUTES == 0) {
		timer->_current_time += timer->_current_delay;
		timer->_current_time % Time_Units::SECONDS == 0 ? timer->_secondTick = true : timer->_secondTick = false;
		timer->_current_time % Time_Units::MINUTES == 0 ? timer->_minuteTick = true : timer->_minuteTick = false;
	}

	return timer->_current_delay;
}