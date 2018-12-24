#include "game.hpp"
#include <iostream>

namespace kdr {
	Game::Game(const char* window_title, int width, int height, bool limit_framerate) {
		window = new Window(*this, window_title, width, height, limit_framerate);
		return;
	}

	Game::Game()
	: window(nullptr) {
		return;
	}
}