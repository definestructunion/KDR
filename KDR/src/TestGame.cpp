#include "TestGame.hpp"
#include <iostream>
#include "gfx/shader.hpp"

namespace kdr {
	mat4* ortho;

	TestGame::TestGame(const char* window_title, int width, int height, bool limit_framerate) {
		loadAssets();
		window = new Window(*this, window_title, width, height, limit_framerate);
		ortho = new mat4(mat4::ortho(0, width, height, 0, -100, 100));
		renderer = new BatchRenderer(TileData(16, 5, 1));
		return;
	}

	Texture* texture;
	Texture* texture2;
	Shader* shader;

	void TestGame::loadAssets() {
		texture = new Texture("res/textures/tb.png");
		texture2 = new Texture("res/textures/tc.png");
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
		shader = new Shader();
		GLint texIDs[] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
		};
		shader->bind();
		shader->setUniform1iv("textures", texIDs, 32);
		shader->setUniformMat4("pr_matrix", *ortho);
		shader->unbind();

		KDR_AddFont(new Font("SourceSansPro", "res/fonts/SourceSansPro-Light.TTF", 12));

		return;
	}

	void TestGame::update() {
		BatchRenderer batch = BatchRenderer(TileData(0, 0, 0));
		window->clear();
		window->update();
		return;
	}

	void TestGame::draw() {
		Font* font = KDR_GetFont("SourceSansPro");
		srand(NULL);
		shader->bind();
		renderer->begin();
		
		//renderer->draw(texture, 1, 1, vec4(1, 1, 1, 1).toColor1());
		for (int y = 0; y < 50; ++y) {
			for (int x = 0; x < 50; ++x) {
				unsigned int col = 0x0;
				Texture* tex = nullptr;
				if ((x + y) % 2 == 1)
					col = vec4(1, 1, 1, 1).toColor1();
				else
					col = vec4(0.5f, 0.5f, 1, 1).toColor1();

				if (rand() % 2 == 1)
					tex = texture;
				else
					tex = texture2;

				renderer->draw(tex, x, y, col);
			}
		}

		
		renderer->drawString("Hello", *font, 0, 0, vec4(1, 1, 1, 1).toColor1());
		renderer->drawString("Test", *font, vec3(500, 500, 0), vec4(1, 1, 1, 1).toColor1());
		renderer->draw(texture, Rectangle(600, 600, 200, 200), vec4(1, 1, 1, 1).toColor1());

		renderer->end();
		renderer->flush();

		shader->unbind();

		window->draw();
		return;
	}

	void TestGame::windowResize() {
		delete ortho;
		ortho = new mat4(mat4::ortho(0, window->getWidth(), window->getHeight(), 0, -100, 100));
		shader->bind();
		shader->setUniformMat4("pr_matrix", *ortho);
		shader->unbind();
		std::cout << "Resized" << std::endl;
		return;
	}

	void TestGame::clean() {
		delete window;
		return;
	}
}