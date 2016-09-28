#include "Light.h"

glm::vec3 defaultAttenuation = glm::vec3(1,1,1);

Light::Light()
	:	Entity(DEFAULT_OBJ, glm::vec3(0,0,0), glm::vec3(1,1,1), 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(char* filepath)
	:	Entity(filepath, glm::vec3(0,0,0), glm::vec3(1,1,1), 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(char* filepath, glm::vec3 _position)
	:	Entity(filepath, _position, glm::vec3(1,1,1), 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(char* filepath, glm::vec3 _position, glm::vec3 _color)
:	Entity(filepath, _position, _color, 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(glm::vec3 _position)
:	Entity(DEFAULT_OBJ, _position, glm::vec3(1,1,1), 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(glm::vec3 _position, glm::vec3 _color)
:	Entity(DEFAULT_OBJ, _position, _color, 0.2f), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}