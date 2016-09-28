#include "PassthroughShader.h"

PassthroughShader::PassthroughShader()
	:	programID(createProgram()), ambientLightFactor(0.2f)
{}

PassthroughShader::PassthroughShader(real32 _alf)
	:		programID(createProgram()), ambientLightFactor(_alf)
{}

void
PassthroughShader::checkShaderCompile(GLuint shader, GLint type)
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
PassthroughShader::checkProgramStatus(GLuint program)
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
PassthroughShader::readShaderCode(char* filename)
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
PassthroughShader::createProgram()
{
	// Delete this shit after
	GLuint program = glCreateProgram();
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VSCString = readShaderCode("passthrough.vertex");
	std::string FSCString = readShaderCode("passthrough.fragment");
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
	glUseProgram(program);

	// Switch
	print("Loading GLSL uniforms...");
	location_pr_matrix = glGetUniformLocation(program, "pr_matrix");
	location_vw_matrix = glGetUniformLocation(program, "vw_matrix");
	location_tr_matrix = glGetUniformLocation(program, "tr_matrix");
	location_rt_matrix = glGetUniformLocation(program, "rt_matrix");
	location_sc_matrix = glGetUniformLocation(program, "sc_matrix");
	location_ambient_light_factor = glGetUniformLocation(program, "ambientLightFactor");
	location_light_position = glGetUniformLocation(program, "lightPosition");
	location_eye_position = glGetUniformLocation(program, "eyePosition");

	/* Add a switch to debug this
	print("location_pr_matrix: " << location_pr_matrix);
	print("location_vw_matrix: " << location_vw_matrix);
	print("location_tr_matrix: " << location_tr_matrix);
	print("location_rt_matrix: " << location_rt_matrix);
	print("location_sc_matrix: " << location_sc_matrix);
	print("location_ambient_light_factor: " << location_ambient_light_factor);
	print("location_light_position: " << location_light_position);
	print("location_eye_position: " << location_eye_position);
	*/

// Update this if you want to use it
#define CHECK_ALL_UNIFORMS
#ifdef CHECK_ALL_UNIFORMS
	if (location_pr_matrix == -1 || location_vw_matrix == -1 || location_tr_matrix == -1 || 
		location_rt_matrix == -1 || location_sc_matrix == -1 || 
		location_ambient_light_factor == -1 || location_light_position == -1 ||
		location_eye_position == -1)
	{
		print("Not all uniforms found!");
		system("PAUSE");
		exit(-1);
	}
#endif
	// Switch
	print("All uniforms found!");

	glUseProgram(0);
	return(program);
}

void
PassthroughShader::enable()
{
	glUseProgram(programID);
}

void
PassthroughShader::disable()
{
	glUseProgram(0);
}

GLuint 
PassthroughShader::get_location_pr_matrix()
{
	return(location_pr_matrix);
}

GLuint 
PassthroughShader::get_location_vw_matrix()
{
	return(location_vw_matrix);
}

GLuint 
PassthroughShader::get_location_tr_matrix()
{
	return(location_tr_matrix);
}

GLuint 
PassthroughShader::get_location_rt_matrix()
{
	return(location_rt_matrix);
}

GLuint 
PassthroughShader::get_location_sc_matrix()
{
	return(location_sc_matrix);
}

GLuint 
PassthroughShader::get_location_ambient_light_factor()
{
	return(location_ambient_light_factor);
}

GLuint 
PassthroughShader::get_location_light_position()
{
	return(location_light_position);
}

GLuint 
PassthroughShader::get_location_eye_position()
{
	return(location_eye_position);
}