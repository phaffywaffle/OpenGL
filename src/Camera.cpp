#include "Camera.h"

glm::vec3 Camera::UP = glm::vec3(0,1,0);

Camera::Camera() 
	:	Entity(0, glm::vec3(0,0,0), glm::vec3(0,0,-1)), right(1,0,0)
{}

Camera::Camera(glm::vec3 _translation)
	:	Entity(0, _translation, glm::vec3(0,0,-1)), right(1,0,0)
{}

// Remember, here rotation is a normalized vector that points the camera, not 3 float angle values
Camera::Camera(glm::vec3 _translation, glm::vec3 _rotation)
	:	Entity(0, _translation, _rotation), right(glm::cross(rotation, UP)) 
{}

Camera::Camera(Model* _model, glm::vec3 _translation, glm::vec3 _rotation, real32 _scale)
	: 	Entity(_model, _translation, _rotation, _scale), right(glm::cross(rotation, UP))
{}

glm::mat4 
Camera::getViewMatrix()
{
	return(glm::lookAt(translation, translation + rotation, UP));
}