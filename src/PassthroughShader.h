#pragma once

#include "defines.h"
#include "Shader.h"

class 
PassthroughShader : public Shader
{
public:
	real32 ambientLightFactor;
private:
	GLuint location_pr_matrix;
	GLuint location_vw_matrix;
	GLuint location_tr_matrix;
	GLuint location_rt_matrix;
	GLuint location_sc_matrix;
	GLuint location_sampler;
	GLuint location_ambient_light_factor;
	GLuint location_light_position;
	GLuint location_eye_position;
public:
	PassthroughShader();
	PassthroughShader(real32);
	void getUniformLocations();
	GLuint get_location_pr_matrix();
	GLuint get_location_vw_matrix();
	GLuint get_location_tr_matrix();
	GLuint get_location_rt_matrix();
	GLuint get_location_sc_matrix();
	GLuint get_location_sampler();
	GLuint get_location_ambient_light_factor();
	GLuint get_location_light_position();
	GLuint get_location_eye_position();
};