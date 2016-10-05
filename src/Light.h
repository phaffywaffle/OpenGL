#pragma once

#include "defines.h"
#include "Entity.h"

// Because rotation isn't shit for lights, super.rotation represents the color (typically (1,1,1))
// Nope, cause if we're gonna render the light model at all it still needs that rotation

class 
Light : public Entity
{
public:
	// Todo(dallas): Fix the shader up a bit
	glm::vec3 color;
	real32 ambientLightFactor;
	// Not currently sending to shader
	glm::vec3 attenuationValues;
	static glm::vec3 defaultAttenuation;
public:
	Light();
	Light(glm::vec3);
	Light(glm::vec3,glm::vec3);
}; 