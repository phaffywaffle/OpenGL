#include "PassthroughShader.h"

PassthroughShader::PassthroughShader()
	:	Shader("shaders/passthrough.vertex", "shaders/passthrough.fragment", "PASSTHROUGH"), ambientLightFactor(0.2f)
{
	getUniformLocations();	
}

PassthroughShader::PassthroughShader(real32 _alf)
	:	Shader("shaders/passthrough.vertex", "shaders/passthrough.fragment", "PASSTHROUGH"), ambientLightFactor(_alf)
{
	getUniformLocations();
}

void
PassthroughShader::getUniformLocations()
{
	enable();

	// Switch
	print("Loading GLSL uniforms...");
	location_pr_matrix = glGetUniformLocation(programID, "pr_matrix");
	location_vw_matrix = glGetUniformLocation(programID, "vw_matrix");
	location_tr_matrix = glGetUniformLocation(programID, "tr_matrix");
	location_rt_matrix = glGetUniformLocation(programID, "rt_matrix");
	location_sc_matrix = glGetUniformLocation(programID, "sc_matrix");
	location_sampler = glGetUniformLocation(programID, "sample");
	location_ambient_light_factor = glGetUniformLocation(programID, "ambientLightFactor");
	location_light_position = glGetUniformLocation(programID, "lightPosition");
	location_eye_position = glGetUniformLocation(programID, "eyePosition");

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
		location_rt_matrix == -1 || location_sc_matrix == -1 || location_sampler == -1 || 
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

	disable();
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
PassthroughShader::get_location_sampler()
{
	return(location_sampler);
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