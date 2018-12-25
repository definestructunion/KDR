#ifndef _KDR_WINDOW_HPP
#define _KDR_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace kdr {
	class Game;

	/*
	 Window of the game
	 Does not have ownership over Game
	 Only calls glewInit once
	 */
	class Window {
	private:
		Game& game;
		GLFWwindow* glfw_window;
		const char* title;
		unsigned short width;
		unsigned short height;
		bool framerate_limited;
		float x, y;

	public:
		/*
		 Creates the window of the game
		 Does not have ownership over Game
		 Only calls glewInit once
		 @param title: title of the window
		 @param width: width of the window in pixels
		 @param height: height of the window in pixels
		 @param limit_framerate: whether or not the game's framerate
		 will be limited by vsync
		 */
		Window(Game& game, const char* title, unsigned short width, unsigned short height, bool limit_framerate);
		/*
		 Deletes the glfw window tied to this class
		 */
		~Window();

		/*
		Updates the window
		Checks for OpenGL errors and
		prints them if any
		Polls events and calls callback
		functions if any events fired
		*/
		void update();

		/*
		 Draws all data bound to the window
		 */
		void draw();

		/*
		 Clears the window of all the rendered data
		 */
		void clear();

		/*
		 Returns whether or not the window should close
		 */
		bool isRunning() const;

		inline const int getWidth() const {
			return width;
		}

		inline const int getHeight() const {
			return height;
		}

		/*
		 Callback function for glfw errors
		 @param error: ID of the error
		 @param description: the error's message
		 */
		friend void errorCallback(int error, const char* description);

		/*
		 Callback function for the glfw window resizing
		 @param window: the glfw window of the window
		 @param width: new window width
		 @param height: new window height
		 */
		friend void windowResize(GLFWwindow *window, int width, int height);

		/*
		 Callback function for glfw setting the KDR keys
		 @param window: the glfw window of the window
		 @param scancode: the code for the key to query
		 @param action: what is happening to the key
		 IE releasing or being pressed
		 @param mods: modifier keys
		 */
		friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/*
		 Callback function for glfw setting the KDR (mouse) buttons
		 @param window: the glfw window of the window
		 @param action: what is happening to the key
		 IE releasing or being pressed
		 @param mods: modifier keys
		 */
		friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		/*
		 Callback function for glfw setting the window's mouse positions
		 @param window: the glfw window of the window
		 */
		friend void cursorPositionCallback(GLFWwindow* window, double x, double y);
	};
}

#endif // hi :)