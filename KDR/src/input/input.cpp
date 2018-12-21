#include "input.hpp"
#include <string.h>
#include <assert.h>

namespace kdr {
	struct KeyState {
		bool keys[MAX_KEYS];
		bool buttons[MAX_BUTTONS];
		KeyState() {
			memset(keys, false, MAX_KEYS);
			memset(buttons, false, MAX_BUTTONS);
			return;
		}
	};

	// represents keys that do fire repeatedly when held down
	KeyState current = KeyState();
	// represents keys that do not fire repeatedly when held down
	KeyState previous = KeyState();
	// represents the keys that glfw sets each window update
	KeyState glfw = KeyState();

	bool KDR_KeyDown(Keys key) {
		return current.keys[(int)key];
	}

	bool KDR_KeyPressed(Keys key) {
		return previous.keys[(int)key];
	}

	bool KDR_ButtonDown(Buttons button) {
		return current.buttons[(int)button];
	}

	bool KDR_ButtonPressed(Buttons button) {
		return previous.buttons[(int)button];
	}

	void KDR_UpdateKeys() {
		for (unsigned short i = 0; i < MAX_KEYS; ++i)
			// since previous keys are keys that are only true for one
			// frame when held down, we need to check if the current key
			// isn't down anymore, but we also need to check if the keys
			// are being pressed down at all, which is where glfw keys comes in
			previous.keys[i] = glfw.keys[i] && !current.keys[i];
		// since current is a POD, we can memcpy without concern
		// and it's faster than a for loop
		memcpy(current.keys, glfw.keys, MAX_KEYS);
		for (unsigned short i = 0; i < MAX_BUTTONS; ++i)
			// since previous buttons are buttons that are only true for one
			// frame when held down, we need to check if the current button
			// isn't down anymore, but we also need to check if the buttons
			// are being pressed down at all, which is where glfw buttons comes in
			previous.buttons[i] = glfw.keys[i] && !current.keys[i];
		// since current is a POD, we can memcpy without concern
		// and it's faster than a for loop
		memcpy(current.buttons, glfw.buttons, MAX_BUTTONS);
		return;
	}

	void KDR_SetKey(int key, bool val) {
		glfw.keys[key] = val;
		return;
	}

	void KDR_SetButton(int button, bool val) {
		glfw.buttons[button] = val;
		return;
	}
}