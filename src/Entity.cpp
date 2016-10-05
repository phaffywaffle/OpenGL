#include "Entity.h"

Entity::Entity(Model* _model)
	:	model(_model), translation(glm::vec3(0,0,0)), rotation(glm::vec3(0,0,0)), scale(1)
{}

Entity::Entity(Model* _model, glm::vec3 _translation)
	: 	model(_model), translation(_translation), rotation(glm::vec3(0,0,0)), scale(1)
{}

Entity::Entity(Model* _model, glm::vec3 _translation, glm::vec3 _rotation)
	: 	model(_model), translation(_translation), rotation(_rotation), scale(1)
{}

Entity::Entity(Model* _model, glm::vec3 _translation, glm::vec3 _rotation, real32 _scale)
	: 	model(_model), translation(_translation), rotation(_rotation), scale(_scale)
{}