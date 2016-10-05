#pragma once

#include "defines.h"

typedef const char* shader_type;

class
Shader
{
public:
	shader_type type;
protected:
	GLuint programID;
public:
	Shader(char*,char*,const char*);
	void enable();
	void disable();
	// Can't do this from the constructor because of complicated C++ memory allocations issues
	// virtual void getUniformLocations() = 0;
	// So the burdon of loading each shader's uniform locations now falls on the shader instead of the base class
	// Poopy, but manageable 
private:
	void checkShaderCompile(GLuint, GLint);
	void checkProgramStatus(GLuint);
	std::string readShaderCode(char*);
	GLuint createProgram(char*,char*);
};