#pragma once

#include "defines.h"
#include "Entity.h"

#define DEFAULT_OBJ "cube.obj"

// Because rotation isn't shit for lights, super.rotation represents the color (typically (1,1,1))

class 
Light : public Entity
{
public:
	// Todo(dallas): Fix the shader up a bit
	real32 ambientLightFactor;
	glm::vec3 attenuationValues;
	static glm::vec3 defaultAttenuation;
public:
	Light();
	Light(char*);
	Light(char*,glm::vec3);
	Light(char*,glm::vec3,glm::vec3);
	Light(glm::vec3);
	Light(glm::vec3,glm::vec3);
}; 