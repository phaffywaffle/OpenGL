#pragma once

#include "defines.h"

class
Model
{
public:
	GLuint vao, vbo, ibo;
	real32* verts;
	uint32 num_verts;
	GLushort* indices;
	uint32 num_indices;
	Model();
	~Model();
	void bind();
	void unbind();
};