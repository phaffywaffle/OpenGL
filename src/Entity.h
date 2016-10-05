#pragma once

#include "defines.h"
#include "Model.h"

class 
Entity
{
public:
	// Make this private someday
	Model* model;
	glm::vec3 translation;
	glm::vec3 rotation;
	real32 scale;
public:
	Entity(Model*);
	Entity(Model*,glm::vec3);
	Entity(Model*,glm::vec3,glm::vec3);
	Entity(Model*,glm::vec3,glm::vec3,real32);
};