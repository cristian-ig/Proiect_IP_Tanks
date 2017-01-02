#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<vector>
#include"Vertex.h"
#include<algorithm>

namespace Engine {

	struct objSprite {
		GLuint texture;
		

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;


	};
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
			offset(Offset), numVertices(NumVertices), texture(Texture)
		{

		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
			
	};

class DrawClass
{

public:
	DrawClass();
	~DrawClass();

	void init();
	void dispose();



private:

	void createVertexArray();

	void begin();

	void addObj(const glm::vec4& quadCoord, const glm::vec4& uvCoord, GLuint texture, const Color& color);
	
	void end();

	void createRenderBatches();

	void Sort();

	static bool compare(objSprite* a, objSprite* b);

	void renderBatch();

	

	GLuint _vao;
	GLuint _vbo;
	std::vector<objSprite*> _spriteObjects;
	std::vector<RenderBatch>_renderBatches;



};

}