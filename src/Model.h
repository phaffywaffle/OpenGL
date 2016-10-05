#pragma once

#include "defines.h"

class
Model
{
public:
	// Keep this?
	char* name;
private:
	GLuint vao, vbo, uvbo, nbo, ibo, texture;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
public:
	Model(char*,char*);
	void bind();
	void unbind();
	uint32 vertCount();
};