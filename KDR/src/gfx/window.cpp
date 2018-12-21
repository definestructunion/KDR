#include <GL/glew.h>
#include "window.hpp"
#include "input/input.hpp"
#include <iostream>
#include <vcruntime_exception.h>

namespace kdr {
	void errorCallback(int error, const char* description) {
		std::cout << description << std::endl;
		return;
	}

	void windowResize(GLFWwindow *window, int width, int height) {
		// set OpenGL's viewport to our width and height
		glViewport(0, 0, width, height);
		// get the current window
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->width = width;
		win->height = height;
		return;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		// get the current window
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		KDR_SetKey(key, action != GLFW_RELEASE);
		return;
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		// get the current window
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		KDR_SetButton(button, action != GLFW_RELEASE);
		return;
	}

	void cursorPositionCallback(GLFWwindow* window, double x, double y) {
		// get the current window
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->x = x;
		win->y = y;
		return;
	}

	Window::Window(const char* title, unsigned short width, unsigned short height, bool limit_framerate)
	: title(title), width(width), height(height), framerate_limited(limit_framerate) {
		// errorCallback is able to be called before glfwInit
		// and glfwInit can fail, so if it does happen, it
		// would be beneficial to see the error
		glfwSetErrorCallback(errorCallback);
		if (!glfwInit()) {
			// terminate glfw
			// make an runtime error message
			// display the message
			glfwTerminate();
			std::runtime_error error = std::runtime_error("GLFW failed to initialize\nAborting creation of window");
			std::cout << error.what() << std::endl;
			throw error;
		}

		glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

		// glfw is initialized now
		// set callback functions that
		// need to be after glfwInit
		// some of these can be before glfwInit though
		glfwMakeContextCurrent(glfw_window);
		glfwSetWindowUserPointer(glfw_window, this);
		glfwSetFramebufferSizeCallback(glfw_window, windowResize);
		glfwSetKeyCallback(glfw_window, keyCallback);
		glfwSetMouseButtonCallback(glfw_window, mouseButtonCallback);
		glfwSetCursorPosCallback(glfw_window, cursorPositionCallback);

		// enable vsync if framerate_limited is true
		// don't limit if false
		glfwSwapInterval(framerate_limited);

		// keep track of whether or not
		// glew has already been intialized
		static bool initted = false;
		if(!initted)
			// if glew failed to initialize
			// send a runtime exception and
			// terminate the currently made
			// glfw window
			if (glewInit() != GLEW_OK) {
				glfwTerminate();
				std::runtime_error error = std::runtime_error("GLEW failed to initialize\nAborting creation of window");
				std::cout << error.what() << std::endl;
				throw error;
			}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
		return;
	}

	Window::~Window() {
		delete glfw_window;
		return;
	}

	void Window::update() {
		KDR_UpdateKeys();
		GLenum errors = glGetError();
		// if there are any errors, print them
		// glGetError clears the first error found
		// from the "list" of errors
		if (errors != GL_NO_ERROR)
			std::cout << "OpenGL error " << errors << std::endl;
		glfwPollEvents();
		glfwSwapBuffers(glfw_window);
		return;
	}

	void Window::clear() {
		// clears the OpenGL color
		// and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}

	bool Window::isRunning() const {
		return !glfwWindowShouldClose(glfw_window);
	}
}