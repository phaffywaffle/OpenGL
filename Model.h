#pragma once

#include "defines.h"

class
Model
{
public:
	GLuint vao, vbo, uvbo, nbo, ibo;
	real32* verts;
	uint32 num_verts;
	real32* uvs;
	real32* normals;
	GLushort* indices;
	uint32 num_indices;
	Model();
	~Model();
	void bind();
	void unbind();
	void processLine(std::string);
};