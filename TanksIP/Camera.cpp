#include "Camera.h"
#include "Defines.h"
namespace Engine {

	Camera::Camera() :
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_screenWidth(SCREEN_WIDTH),
		_screenHeight(SCREEN_HEIGHT),
		_position(0, 0),
		_update(true)
	{
		
	}


	Camera::~Camera()
	{
	}

	void Camera::init(int screenWidth, int screenHeight) {

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	glm::vec2 Camera::convertToWorldCoordonates(glm::vec2 screenCoords) {

		// Invert Y direction
		screenCoords.y = _screenHeight - screenCoords.y;

		// Make it so that 0 is the center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		// Scale the coordinates
		screenCoords /= _scale;

		// Translate with the camera position
		screenCoords += _position;

		return screenCoords;


	}
	void Camera::update() {

		if (_update) {

			//Camera translation
			glm::vec3 translation(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translation);

			//Camera scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale)*_cameraMatrix;

			_update = false;

		}

	}
	bool Camera::checkIfInView(const glm::vec2& position, const glm::vec2& dimension) {

		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / (_scale);

		// The minimum distance before a collision occurs
		const float MIN_DISTANCE_X = dimension.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimension.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		// Center position of the parameters
		glm::vec2 centerPos = position + dimension / 2.0f;
		// Center position of the camera
		glm::vec2 centerCameraPos = _position;
		// Vector from the input to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		// Get the depth of the collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// If both the depths are > 0, then we collided
		if (xDepth > 0 && yDepth > 0) {
			// There was a collision
			return true;
		}
		return false;

	}
}