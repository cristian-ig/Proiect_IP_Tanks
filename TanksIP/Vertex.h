#pragma once
#include <gl/glew.h>

namespace tanks
{

struct Position
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Color
{
	GLubyte R;
	GLubyte G;
	GLubyte B;
	GLubyte A; //alpha 

	Color() //auto 0
	{
		R = G = B = A = 0;
	}

	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) //set custom colors
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

};

struct UV  //normalized coordonates of the textires
{
	float u = 0.0f; // x axes
	float v = 0.0f; // reversed y axes
};

struct Vertex //we could've used vectors but this makes more sense
{			//using a struct instead of a class because it just holds data
	Position pos;
	Color color;
	UV uv;

	//Setters
	void setPosition(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.R = r;
		color.G = g;
		color.B = b;
		color.A = a;
	}

	void setUV(float u, float v) 
	{
		uv.u = u;
		uv.v = v;
	}
};

}