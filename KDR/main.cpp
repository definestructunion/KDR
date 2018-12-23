#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <exception>
#include <vector>
#include <iostream>
#include "gfx/window.hpp"
#include "input/input.hpp"
#include "util/utilfiles.hpp"
#include "gfx/shader.hpp"

int main(void)
{
	using namespace kdr;

	kdr::Window* window = new Window("KDR", 500, 500, true);

	Shader* shader = new Shader("res/shaders/basic.shader", true, "#shader", "vertex", "fragment");
	Shader* shader2 = new Shader();

	while (window->isRunning()) {
		window->clear();
		window->update();
	}

	return 0;
}