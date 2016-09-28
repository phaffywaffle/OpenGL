#pragma once

#include "defines.h"
#include "Model.h"

class 
Entity
{
private: 
	Model model;
public:
	glm::vec3 translation;
	glm::vec3 rotation;
	real32 scale;
public:
	Entity(char*);
	Entity(char*,glm::vec3);
	Entity(char*,glm::vec3,glm::vec3);
	Entity(char*,glm::vec3,glm::vec3,real32);
	Entity(Model);
	Entity(Model,glm::vec3);
	Entity(Model,glm::vec3,glm::vec3);
	Entity(Model,glm::vec3,glm::vec3,real32);
	Model getModel();
};