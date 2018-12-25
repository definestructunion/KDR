#include "base/game.hpp"
#include "gfx/renderers/batchrenderer.hpp"

namespace kdr {
	class TestGame : public Game {
	public:
		BatchRenderer* renderer;
		TestGame(const char* window_title, int width, int height, bool limit_framerate);

		void loadAssets() override;
		int run() override;
		void init() override;
		void update() override;
		void draw() override;
		void windowResize() override;
		void clean() override;
	};
}