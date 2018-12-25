#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <exception>
#include <vector>
#include <iostream>
#include "base/game.hpp"
#include "input/input.hpp"
#include "util/utilfiles.hpp"
#include "gfx/shader.hpp"
#include "TestGame.hpp"
#include "gfx/renderers/renderer.hpp"
#include "gfx/renderers/batchrenderer.hpp"

int main(void)
{
	using namespace kdr;
	Game* game = new TestGame("KDR Engine", 500, 500, false);
	int result = game->run();
	delete game;
	return result;
}