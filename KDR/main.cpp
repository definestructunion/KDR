#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <exception>
#include <vector>
#include <iostream>
#include "gfx/window.hpp"
#include "input/input.hpp"

int main(void)
{
	using namespace kdr;

	kdr::Window* window = new Window("KDR", 500, 500, true);

	while (window->isRunning()) {
		window->clear();
		window->update();
	}

	return 0;
}