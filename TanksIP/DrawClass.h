#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<vector>
#include"Vertex.h"

namespace Engine {


class Quad {
public:
	Quad() {};
	Quad(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color);
	Quad(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle);
	
	GLuint offset;
	GLuint numVertices;
	GLuint texture;

	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;

private:
	// Rotates a point about (0,0) by angle
	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

};

struct Render
{
Render(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
	numVertices(NumVertices), texture(Texture)
{
}
GLuint offset;
GLuint numVertices;
GLuint texture;
};



class DrawSprites
{
public:
	DrawSprites();
	~DrawSprites();

	// Initializes the spritebatch
	void init();
	void dispose();

	// Begins the spritebatch
	void begin();

	// Ends the spritebatch
	void end();

	// Adds a glyph to the spritebatch
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
	// Adds a glyph to the spritebatch with rotation
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle);
	// Adds a glyph to the spritebatch with rotation
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2& dir);

	// Renders the entire SpriteBatch to the screen
	void renderBatch();

private:
	// Creates all the needed RenderBatches
	void createRenderBatches();

	// Generates our VAO and VBO
	void createVertexArray();

	// Sorts glyphs according to _sortType
	void sortGlyphs();

	// Comparator
	static bool compareTexture(Quad* a, Quad* b);

	GLuint _vbo;
	GLuint _vao;

	std::vector<Quad*> _quadPtr; ///< This is for sorting
	std::vector<Quad> _quads; ///< These are the actual glyphs
	std::vector<Render> _renderBatches;
};
}