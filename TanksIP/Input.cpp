#include "Input.h"

namespace tanks {

Input::Input()
{
}


Input::~Input()
{
}
void Input::update() {
	// Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
	//using a for each loop with an iterator
	for (auto& it : _keyMap) {
		_previousKeyMap[it.first] = it.second;
	}
}

void Input::pressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	//and it's more efficient in terms of memory
	_keyMap[keyID] = true;
}

void Input::releaseKey(unsigned int keyID) {
	//when we release a key the boolean value in the map is going to be false
	_keyMap[keyID] = false;
}

void Input::setMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;	
}

bool Input::isKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool Input::isKeyPressed(unsigned int keyID) {
	// Check if it is pressed this frame, and wasn't pressed last frame
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
		return true;
	}
	return false;
}

bool Input::wasKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

}