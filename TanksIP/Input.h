#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

namespace tanks {

// Input manager stores a key map that maps SDL_Keys to booleans.
// If the value in the key map is true, then the key is pressed.
// Otherwise, it is released.
// We gonna use an unordered map to store all they key and a bool that determinates
// if the key is or was pressed

	class Input
{
public:
	Input();
	~Input();

	void update();
	///KEY STATES
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	/// Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);
	/// Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID);

	//setters and getters
	void setMouseCoords(float x, float y);
	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	/// Returns true if the key is held down
	bool wasKeyDown(unsigned int keyID);

	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previousKeyMap;
	glm::vec2 _mouseCoords = glm::vec2(0.0f, 0.0f);
	};
}
