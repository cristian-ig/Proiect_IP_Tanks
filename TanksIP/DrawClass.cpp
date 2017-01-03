#include "DrawClass.h"


namespace Engine {


	DrawClass::DrawClass() : _vbo(0), _vao(0)
	{
	}


	DrawClass::~DrawClass()
	{
	}

	void DrawClass::init() {

		createVertexArray();
	}

	void DrawClass::dispose() {

		if (_vao != 0) {
			glDeleteVertexArrays(1, &_vao);
			_vao = 0;
		}
		if (_vbo != 0) {
			glDeleteVertexArrays(1, &_vbo);
			_vbo = 0;
		}

	}


	void DrawClass::createVertexArray() {

		//GenBuffers if not generated and bind them
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);

		glBindVertexArray(_vao);

		if (_vbo == 0)
			glGenVertexArrays(1, &_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Enable attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Attribute pointers : position color uv
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void DrawClass::begin() {

		_renderBatches.clear();
		for (size_t i = 0; i < _spriteObjects.size(); i++) {

			delete _spriteObjects[i];
		}
		_spriteObjects.clear();

	}

	void DrawClass::addObj(const glm::vec4& quadCoord, const glm::vec4& uvCoord, GLuint texture, const Color& color) {
		//Create a new object with the input parameters and adds it to the list
		objSprite* newSpriteObj = new objSprite;
		newSpriteObj->texture = texture;

		newSpriteObj->topLeft.color = color;
		newSpriteObj->topLeft.setPosition(quadCoord.x, quadCoord.y + quadCoord.w);
		newSpriteObj->topLeft.setUV(uvCoord.x, uvCoord.y + uvCoord.w);

		newSpriteObj->bottomLeft.color = color;
		newSpriteObj->bottomLeft.setPosition(quadCoord.x, quadCoord.y);
		newSpriteObj->bottomLeft.setUV(uvCoord.x, uvCoord.y);

		newSpriteObj->bottomRight.color = color;
		newSpriteObj->bottomRight.setPosition(quadCoord.x + quadCoord.z, quadCoord.y);
		newSpriteObj->bottomRight.setUV(uvCoord.x + uvCoord.z, uvCoord.y);

		newSpriteObj->topRight.color = color;
		newSpriteObj->topRight.setPosition(quadCoord.x + quadCoord.z, quadCoord.y + quadCoord.w);
		newSpriteObj->topRight.setUV(uvCoord.x + uvCoord.z, uvCoord.y + uvCoord.w);

		_spriteObjects.push_back(newSpriteObj);

	}

	void DrawClass::addObj(const glm::vec4& quadCoord, const glm::vec4& ucCoord, GLuint Texture, float Depth, const Color& color, float angle) {

		objSprite* newSpriteObj = new objSprite;

		newSpriteObj->texture = Texture;

		glm::vec2 halfDims(quadCoord.z / 2.0f, quadCoord.w / 2.0f);

		// Get points centered at origin
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;

		newSpriteObj->topLeft.color = color;
		newSpriteObj->topLeft.setPosition(quadCoord.x + tl.x, quadCoord.y + tl.y);
		newSpriteObj->topLeft.setUV(ucCoord.x, ucCoord.y + ucCoord.w);

		newSpriteObj->bottomLeft.color = color;
		newSpriteObj->bottomLeft.setPosition(quadCoord.x + bl.x, quadCoord.y + bl.y);
		newSpriteObj->bottomLeft.setUV(ucCoord.x, ucCoord.y);

		newSpriteObj->bottomRight.color = color;
		newSpriteObj->bottomRight.setPosition(quadCoord.x + br.x, quadCoord.y + br.y);
		newSpriteObj->bottomRight.setUV(ucCoord.x + ucCoord.z, ucCoord.y);

		newSpriteObj->topRight.color = color;
		newSpriteObj->topRight.setPosition(quadCoord.x + tr.x, quadCoord.y + tr.y);
		newSpriteObj->topRight.setUV(ucCoord.x + ucCoord.z, ucCoord.y + ucCoord.w);

		_spriteObjects.push_back(newSpriteObj);
	}

	glm::vec2 DrawClass::rotatePoint(const glm::vec2& pos, float angle)
	{

		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newv;
	}

void DrawClass::Sort() {

	//Sorts the objects by texture
	std::stable_sort(_spriteObjects.begin(), _spriteObjects.end(), compare);

}

bool DrawClass::compare(objSprite * a, objSprite * b) {

	return (a->texture < b->texture);
}

void DrawClass::end() {

	Sort();
	createRenderBatches();

}

void DrawClass::createRenderBatches() {

	std::vector<Vertex> vertices;
	//resize the vector to the amount of vertices to be drawn
	vertices.resize(_spriteObjects.size() * 6);

	int offset = 0; // current offset
	int cv = 0; // current vertex

				//Add the first batch
	_renderBatches.emplace_back(offset, 6, _spriteObjects[0]->texture);
	vertices[cv++] = _spriteObjects[0]->topLeft;
	vertices[cv++] = _spriteObjects[0]->bottomLeft;
	vertices[cv++] = _spriteObjects[0]->bottomRight;
	vertices[cv++] = _spriteObjects[0]->bottomRight;
	vertices[cv++] = _spriteObjects[0]->topRight;
	vertices[cv++] = _spriteObjects[0]->topLeft;
	offset += 6;

	//Add all the rest of the objects
	for (size_t cg = 1; cg < _spriteObjects.size(); cg++) {

		// Check if this object can be part of the current batch
		if (_spriteObjects[cg]->texture!= _spriteObjects[cg - 1]->texture) {
			// Make a new batch
			_renderBatches.emplace_back(offset, 6, _spriteObjects[cg]->texture);
		}
		else {
			// If its part of the current batch, just increase numVertices
			_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = _spriteObjects[cg]->topLeft;
		vertices[cv++] = _spriteObjects[cg]->bottomLeft;
		vertices[cv++] = _spriteObjects[cg]->bottomRight;
		vertices[cv++] = _spriteObjects[cg]->bottomRight;
		vertices[cv++] = _spriteObjects[cg]->topRight;
		vertices[cv++] = _spriteObjects[cg]->topLeft;
		offset += 6;
	}

	// Bind buffer and upload data
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void DrawClass::renderBatch() {

	glBindVertexArray(_vao);

	for (size_t i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);

}

}
