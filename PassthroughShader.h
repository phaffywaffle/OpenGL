#pragma once

#include "defines.h"

class 
PassthroughShader
{
private:
	GLuint programID;
	GLuint location_pr_matrix;
	GLuint location_vw_matrix;
	GLuint location_tr_matrix;
	GLuint location_rt_matrix;
	GLuint location_sc_matrix;
	GLuint location_ambient_light_factor;
	GLuint location_light_position;
	GLuint location_eye_position;
public:
	PassthroughShader();
	PassthroughShader(real32);
	void enable();
	void disable();
	GLuint get_location_pr_matrix();
	GLuint get_location_vw_matrix();
	GLuint get_location_tr_matrix();
	GLuint get_location_rt_matrix();
	GLuint get_location_sc_matrix();
	GLuint get_location_ambient_light_factor();
	GLuint get_location_light_position();
	GLuint get_location_eye_position();
	real32 ambientLightFactor;
private:
	void checkShaderCompile(GLuint, GLint);
	void checkProgramStatus(GLuint);
	std::string readShaderCode(char*);
	GLuint createProgram();
};