#include<iostream>
#include<algorithm>
#include "DrawClass.h"
const int six = 6;

namespace Engine {

  Quad::Quad(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color) :
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

	Quad::Quad(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle) :
        texture(Texture),
        depth(Depth) {

        glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

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

        topLeft.color = color;
        topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
        topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

        bottomLeft.color = color;
        bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
        bottomLeft.setUV(uvRect.x, uvRect.y);

        bottomRight.color = color;
        bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
        bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

        topRight.color = color;
        topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
        topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

    glm::vec2 Quad::rotatePoint(const glm::vec2& pos, float angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
    }

DrawSprites::DrawSprites() : _vbo(0), _vao(0)
{
}

DrawSprites::~DrawSprites()
{
}

void DrawSprites::init() {
    createVertexArray();
}

void DrawSprites::dispose() {
    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
    if (_vbo != 0) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
}


void DrawSprites::begin() {
    _renderBatches.clear();
   
    // Makes _glpyhs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    _quads.clear();
}

void DrawSprites::end() {
    // Set up all pointers for fast sorting
    _quadPtr.resize(_quads.size());
    for (size_t i = 0; i < _quads.size(); i++) {
        _quadPtr[i] = &_quads[i];
    }

    sortGlyphs();
    createRenderBatches();
	//dispose();
}

void DrawSprites::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
	_quads.emplace_back(destRect, uvRect, texture, depth, color);
}

void DrawSprites::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle) {
	_quads.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void DrawSprites::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2& dir) {
    const glm::vec2 right(1.0f, 0.0f);
    float angle = acos(glm::dot(right, dir));
    if (dir.y < 0.0f) angle = -angle;

    _quads.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void DrawSprites::renderBatch() {
	//_vbo = 1; 
	//_vao = 1;
    // Bind our VAO. This sets up the opengl state we need, including the 
    // vertex attribute pointers and it binds the VBO
    glBindVertexArray(_vao);

    for (size_t i = 0; i < _renderBatches.size(); i++) {
		
        glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

        glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
    }

    glBindVertexArray(0);
}

void DrawSprites::createRenderBatches() {
    // This will store all the vertices that we need to upload
    std::vector <Vertex> vertices;
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    vertices.resize(_quadPtr.size() * six);

    if (_quadPtr.empty()) {
        return;
    }

    int offset = 0; // current offset
    int cv = 0; // current vertex

    //Add the first batch
    _renderBatches.emplace_back(offset, six, _quadPtr[0]->texture);
    vertices[cv++] = _quadPtr[0]->topLeft;
    vertices[cv++] = _quadPtr[0]->bottomLeft;
    vertices[cv++] = _quadPtr[0]->bottomRight;
    vertices[cv++] = _quadPtr[0]->bottomRight;
    vertices[cv++] = _quadPtr[0]->topRight;
    vertices[cv++] = _quadPtr[0]->topLeft;
    offset += six;

    //Add all the rest of the glyphs
    for (size_t cg = 1; cg < _quadPtr.size(); cg++) {

        // Check if this glyph can be part of the current batch
        if (_quadPtr[cg]->texture != _quadPtr[cg - 1]->texture) {
            // Make a new batch
            _renderBatches.emplace_back(offset, six, _quadPtr[cg]->texture);
        } else {
            // If its part of the current batch, just increase numVertices
            _renderBatches.back().numVertices += six;
        }
        vertices[cv++] = _quadPtr[cg]->topLeft;
        vertices[cv++] = _quadPtr[cg]->bottomLeft;
        vertices[cv++] = _quadPtr[cg]->bottomRight;
        vertices[cv++] = _quadPtr[cg]->bottomRight;
        vertices[cv++] = _quadPtr[cg]->topRight;
        vertices[cv++] = _quadPtr[cg]->topLeft;
        offset += six;
    }

    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void DrawSprites::createVertexArray() {

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

void DrawSprites::sortGlyphs() 
{
 std::stable_sort(_quadPtr.begin(), _quadPtr.end(), compareTexture);
}

bool DrawSprites::compareTexture(Quad* a, Quad* b) {
    return (a->texture < b->texture);
}
}
