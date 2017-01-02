#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace Engine {
	class Camera
	{
	public:
		Camera();
		~Camera();

		void init(int width, int height);

		void update();

		glm::vec2 convertToWorldCoordonates(glm::vec2 screenCoords);
		bool checkIfInView(const glm::vec2& position, const glm::vec2& dimension);
		const glm::mat4& getCameraMatrix() const { return _cameraMatrix; }
		void offsetPosition(const glm::vec2& offset) { _position += offset; _update = true; }
		void setPosition(const glm::vec2& offset) { _position = offset; _update = true; }
		void offsetScale(float offset) { _scale += offset; if (_scale < 0.001f) _scale = 0.001f; _update = true; }

	private:

		int _screenWidth, _screenHeight;
		float _scale;
		bool _update;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;


	};
}

