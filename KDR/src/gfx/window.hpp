#ifndef _KDR_WINDOW_HPP
#define _KDR_WINDOW_HPP

#include <GLFW/glfw3.h>

namespace kdr {
	/*
	 Window of the game
	 Only calls glewInit once
	 */
	class Window {
	private:
		GLFWwindow* glfw_window;
		const char* title;
		unsigned short width;
		unsigned short height;
		bool framerate_limited;
		float x, y;

	public:
		/*
		 Creates the window of the game
		 Only calls glewInit once
		 title: title of the window
		 width: width of the window in pixels
		 height: height of the window in pixels
		 limit_framerate: whether or not the game's framerate
		 will be limited by vsync
		 */
		Window(const char* title, unsigned short width, unsigned short height, bool limit_framerate);
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
		 Clears the window of all the rendered data
		 */
		void clear();

		/*
		 Returns whether or not the window should close
		 */
		bool isRunning() const;

		/*
		 Callback function for glfw errors
		 */
		friend void errorCallback(int error, const char* description);

		/*
		 Callback function for the glfw window resizing
		 */
		friend void windowResize(GLFWwindow *window, int width, int height);

		/*
		 Callback function for glfw setting the KDR keys
		 */
		friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/*
		 Callback function for glfw setting the KDR (mouse) buttons
		 */
		friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		/*
		 Callback function for glfw setting the window's mouse positions
		 */
		friend void cursorPositionCallback(GLFWwindow* window, double x, double y);
	};
}

#endif // hi :)