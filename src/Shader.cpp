#include "Shader.h"

Shader::Shader(char* vertexFilePath, char* fragmentFilePath, shader_type _type)
	: 	programID(createProgram(vertexFilePath, fragmentFilePath)), type(_type)
{}

void
Shader::checkShaderCompile(GLuint shader, GLint type)
{
	GLint compileStatus;
	GLint infoLength;
	GLchar* buffer = {};

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		buffer = new GLchar[infoLength];
		// Might throw error
		glGetShaderInfoLog(shader, infoLength, 0, buffer);
		if (type == GL_VERTEX_SHADER) std::cout << "Errors in vertex shader: " << buffer << std::endl;
		else if (type == GL_FRAGMENT_SHADER) std::cout << "Errors in fragment shader: " << buffer << std::endl;
		pause();
		exit(-1);
	}

	delete[] buffer;
}

void
Shader::checkProgramStatus(GLuint program)
{
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		GLchar* buffer = new GLchar[infoLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(program, infoLength, &bufferSize, buffer);
		std::cout << "Error linking program: " << buffer << std::endl;
		delete[] buffer;
		pause();
		exit(-1);
	}
}

std::string
Shader::readShaderCode(char* filename)
{
	std::ifstream input(filename);
	if (!input.good())
	{
		print("File " << filename << " failed to load.");
		pause();
		exit(-1);
	}

	return(std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>()));
}

GLuint
Shader::createProgram(char* vertexFilePath, char* fragmentFilePath)
{
	// Delete this shit after
	GLuint program = glCreateProgram();
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VSCString = readShaderCode(vertexFilePath);
	std::string FSCString = readShaderCode(fragmentFilePath);
	const char* vertexShaderCode = VSCString.c_str();
	const char* fragmentShaderCode = FSCString.c_str();

	glShaderSource(vertShader, 1, &vertexShaderCode, 0);
	glShaderSource(fragShader, 1, &fragmentShaderCode, 0);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	checkShaderCompile(vertShader, GL_VERTEX_SHADER);
	checkShaderCompile(fragShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);
	checkProgramStatus(program); 
	


	return(program);
}

void
Shader::enable()
{
	glUseProgram(programID);
}

void
Shader::disable()
{
	glUseProgram(0);
}