// A WINDOW OBJECT MUST BE CREATED BEFORE A CAMERA CAN BE USED

#pragma once 

#include "defines.h"
#include "Entity.h"

class 
Camera : public Entity
{
public:
	Camera();
	Camera(glm::vec3);
	Camera(glm::vec3, glm::vec3);
	Camera(Model*, glm::vec3, glm::vec3, real32);
	global glm::vec3 UP;
	glm::vec3 right;
	glm::mat4 getViewMatrix();
};