#include "Light.h"

glm::vec3 defaultAttenuation = glm::vec3(1,1,1);

Light::Light()
	:	Entity(0, glm::vec3(0,0,0), glm::vec3(0,0,0), 0.1f), color(glm::vec3(1,1,1)), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(glm::vec3 _position)
	:	Entity(0, _position, glm::vec3(0,0,0), 0.2f), color(glm::vec3(1,1,1)), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}

Light::Light(glm::vec3 _position, glm::vec3 _color)
:	Entity(0, _position, glm::vec3(0,0,0), 0.2f), color(_color), ambientLightFactor(0.2f), attenuationValues(glm::vec3(1.0f, 0.1f, 0.01f))
{}