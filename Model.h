#pragma once

#include "defines.h"

class
Model
{
private:
	GLuint vao, vbo, uvbo, nbo, ibo;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
public:
	Model(char*);
	void bind();
	void unbind();
	uint32 vertCount();
};