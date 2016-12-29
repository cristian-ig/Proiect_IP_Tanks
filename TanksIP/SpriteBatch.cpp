#include "SpriteBatch.h"
#include <algorithm>
#include<iostream>

namespace Engine {


	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color) :
		texture(Texture),
		depth(Depth) {

		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}


	glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle) {
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newv;
	}

	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init() {
		createVertexArray();
	}

	void SpriteBatch::dispose() {
		if (_vao != 0) {
			glDeleteVertexArrays(1, &_vao);
			_vao = 0;
		}
		if (_vbo != 0) {
			glDeleteBuffers(1, &_vbo);
			_vbo = 0;
		}
	}

	void SpriteBatch::begin() {
		_renderBatches.clear();
		// Makes _glpyhs.size() == 0, however it does not free internal memory.
		// So when we later call emplace_back it doesn't need to internally call new.
		_glyphs.clear();
	}

	void SpriteBatch::end() {
		// Set up all pointers for fast sorting
		try {
			_glyphPointers.resize(_glyphs.size());
			for (size_t i = 0; i < _glyphs.size(); i++) {
				_glyphPointers[i] = &_glyphs[i];
				//std::cout << _glyphPointers[i] << std::endl;
			}
			sortGlyphs();
			createRenderBatches();
		}
		catch (int ex) {
			std::cout << "spritebatch end err"; throw ex;
		}
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
		try {
			_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
		}
		catch (int ex) { std::cout << "Spritebatch draw err"; throw ex; }
	}

	void SpriteBatch::renderBatch() {

		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		//PROGRAM BREAKS HERE
		
		try {
			glBindVertexArray(_vao);
			std::cout << &_vao << std::endl;
		for (size_t i = 0; i < _renderBatches.size(); i++) {
			std::cout << &_renderBatches[i] << std::endl;;
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);//PROGRAM BREAKS AFTER THIS
		}

		glBindVertexArray(0);
		} catch (...) { std::cout << "glBindVertexArray(vao) error";  }

	}

	void SpriteBatch::createRenderBatches() {
		// This will store all the vertices that we need to upload
		std::vector <Vertex> vertices;
		// Resize the buffer to the exact size we need so we can treat
		// it like an array
		vertices.resize(_glyphPointers.size() * 6);

		if (_glyphPointers.empty()) {
			std::cout << "glyphpointers empty" << std::endl;
			return;
		}

		int offset = 0; // current offset
		int cv = 0; // current vertex

					//Add the first batch
		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
		vertices[cv++] = _glyphPointers[0]->topLeft;
		vertices[cv++] = _glyphPointers[0]->bottomLeft;
		vertices[cv++] = _glyphPointers[0]->bottomRight;
		vertices[cv++] = _glyphPointers[0]->bottomRight;
		vertices[cv++] = _glyphPointers[0]->topRight;
		vertices[cv++] = _glyphPointers[0]->topLeft;
		offset += 6;
		try {
			//Add all the rest of the glyphs
			for (size_t cg = 1; cg < _glyphPointers.size(); cg++) {

				// Check if this glyph can be part of the current batch
				if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
					// Make a new batch
					_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
				}
				else {
					// If its part of the current batch, just increase numVertices
					_renderBatches.back().numVertices += 6;
				}
				vertices[cv++] = _glyphPointers[cg]->topLeft;
				vertices[cv++] = _glyphPointers[cg]->bottomLeft;
				vertices[cv++] = _glyphPointers[cg]->bottomRight;
				vertices[cv++] = _glyphPointers[cg]->bottomRight;
				vertices[cv++] = _glyphPointers[cg]->topRight;
				vertices[cv++] = _glyphPointers[cg]->topLeft;
				offset += 6;
			}
		}
		catch (int ex) { std::cout << "glyph err"; throw ex; }

		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// Orphan the buffer (for speed)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray() {
		try {
			// Generate the VAO if it isn't already generated
			if (_vao == 0) {
				glGenVertexArrays(1, &_vao);
			}

			// Bind the VAO. All subsequent opengl calls will modify it's state.
			glBindVertexArray(_vao);

			//G enerate the VBO if it isn't already generated
			if (_vbo == 0) {
				glGenBuffers(1, &_vbo);
			}
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);

			//Tell opengl what attribute arrays we need
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			//This is the position attribute pointer
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
			//This is the color attribute pointer
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
			//This is the UV attribute pointer
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

			glBindVertexArray(0);
		}
		catch (int ex) { std::cout << "create vertex array error"; throw ex; }
	}

	void SpriteBatch::sortGlyphs() 
	{
		try {
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
		}
		catch (...) { std::cout << "sortGlyph err";  }
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		try {
			//std::cout << a << " " << b << std::endl;
			return (a->texture < b->texture);
		}
		catch (int ex) {
			std::cout << "comapre texture err"; throw ex;
		}
	}

}