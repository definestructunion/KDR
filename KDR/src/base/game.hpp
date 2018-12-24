#ifndef _KDR_GAME_HPP
#define _KDR_GAME_HPP

// TODO: Turn functions into pure virtual, mark Game abstract, remove game.cpp

#include "gfx/window.hpp"

namespace kdr {
	/*
	 Entry point of the application
	 This is the base of all updating,
	 rendering, initialization, and drawing goes
	 */
	class Game {
	private:


	protected:


	public:
		/*
		 Creates a game to be run
		 @param window_title: the characters to be displayed
		 on the window
		 @param width: the width of the screen in pixels
		 @param height: the height of the screen in pixels
		 @param limit_framerate: whether or not the game will
		 be limited by vsync
		 */
		Game(const char* window_title, int width, int height, bool limit_framerate);

		/*
		 Allows a customizable Game to be made in initialization
		 */
		Game();

		/*
		 The game's window context
		 */
		Window* window;

		virtual void loadAssets() = 0;
		virtual int run() = 0;
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void windowResize() = 0;
		virtual void clean() = 0;
	};
}

#endif // hi :)