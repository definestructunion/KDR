#include "TestGame.hpp"
#include <iostream>

namespace kdr {
	TestGame::TestGame(const char* window_title, int width, int height, bool limit_framerate) {
		loadAssets();
		window = new Window(*this, window_title, width, height, limit_framerate);
		return;
	}

	void TestGame::loadAssets() {
		std::cout << "Loaded Assets" << std::endl;
	}

	int TestGame::run() {
		init();
		while (window->isRunning()) {
			update();
			draw();
		}

		return EXIT_SUCCESS;
	}

	void TestGame::init() {
		return;
	}

	void TestGame::update() {
		window->clear();
		window->update();
		return;
	}

	void TestGame::draw() {
		window->draw();
		return;
	}

	void TestGame::windowResize() {
		std::cout << "Resized" << std::endl;
		return;
	}

	void TestGame::clean() {
		delete window;
		return;
	}
}