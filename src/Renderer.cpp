#include "Renderer.h"

glm::mat4 Renderer::pr_matrix = glm::perspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
glm::mat4 Renderer::vw_matrix = glm::mat4();
glm::mat4 Renderer::tr_matrix = glm::mat4();
glm::mat4 Renderer::rt_matrix = glm::mat4();
glm::mat4 Renderer::sc_matrix = glm::mat4();

bool Renderer::shouldRenderLights = false;

Renderer::Renderer(Camera* _camera, Light* _light)
	:	camera(_camera), light(_light)
{
	passthrough_shader.enable();
	glUniformMatrix4fv(passthrough_shader.get_location_pr_matrix(), 1, GL_FALSE, &pr_matrix[0][0]);
	glUniform1fv(passthrough_shader.get_location_ambient_light_factor(), 1, &passthrough_shader.ambientLightFactor);
	passthrough_shader.disable();
}

void
Renderer::render()
{
	passthrough_shader.enable();
	vw_matrix = camera->getViewMatrix();
	glUniformMatrix4fv(passthrough_shader.get_location_vw_matrix(), 1, GL_FALSE, &vw_matrix[0][0]);
	glUniform3fv(passthrough_shader.get_location_light_position(), 1, &light->translation[0]);
	glUniform3fv(passthrough_shader.get_location_eye_position(), 1, &camera->translation[0]);
	renderEntities();
	if(shouldRenderLights) renderLights();
	passthrough_shader.disable();
}

void Renderer::renderEntities()
{ 
	if(entityMap.empty()) { print("No entities to render"); return; }
	map_type::iterator it = entityMap.begin();
	while(it != entityMap.end())
	{
		Model* m = it->first;
		std::vector<Entity*>* v = it->second;
		m->bind();
		for(uint32 i = 0; i < v->size(); i++)
		{
			Entity* entity = v->at(i);
			tr_matrix = glm::translate(entity->translation);
			rt_matrix = glm::rotate(entity->rotation.x, X_AXIS) * glm::rotate(entity->rotation.y, Y_AXIS) * glm::rotate(entity->rotation.z, Z_AXIS);
			sc_matrix = glm::scale(glm::vec3(entity->scale,entity->scale,entity->scale));
			glUniformMatrix4fv(passthrough_shader.get_location_tr_matrix(), 1, GL_FALSE, &tr_matrix[0][0]);
			glUniformMatrix4fv(passthrough_shader.get_location_rt_matrix(), 1, GL_FALSE, &rt_matrix[0][0]);
			glUniformMatrix4fv(passthrough_shader.get_location_sc_matrix(), 1, GL_FALSE, &sc_matrix[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, FLOATS_PER_VERTEX * entity->model->vertCount());
		}
		m->unbind();
		it++;
	}
}

void
Renderer::renderLights()
{
	light->model->bind();
	tr_matrix = glm::translate(light->translation);
	rt_matrix = glm::rotate(light->rotation.x, X_AXIS) * glm::rotate(light->rotation.y, Y_AXIS) * glm::rotate(light->rotation.z, Z_AXIS);
	sc_matrix = glm::scale(glm::vec3(light->scale,light->scale,light->scale));
	glUniformMatrix4fv(passthrough_shader.get_location_tr_matrix(), 1, GL_FALSE, &tr_matrix[0][0]);
	glUniformMatrix4fv(passthrough_shader.get_location_rt_matrix(), 1, GL_FALSE, &rt_matrix[0][0]);
	glUniformMatrix4fv(passthrough_shader.get_location_sc_matrix(), 1, GL_FALSE, &sc_matrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, FLOATS_PER_VERTEX * light->model->vertCount());
	light->model->unbind();
}

void
Renderer::addEntity(Entity* e)
{
	map_type::iterator it = entityMap.find(e->model);
	// If the model doesn't already exist
	std::vector<Entity*>* temp;
	if(it == entityMap.end())
	{
		// We have to destroy now
		temp  = new std::vector<Entity*>;
		temp->push_back(e);
		entityMap.insert(std::make_pair(e->model, temp));
	}
	else
	{
		temp = it->second;
		temp->push_back(e);
	}
}

uint32 
Renderer::numEntites(Model* model)
{
	return(entityMap.find(model)->second->size());
}

Model* 
Renderer::modelPointer(Model* model)
{
	map_type::iterator it = entityMap.find(model);
	if(it == entityMap.end()) return(0);
	return(it->first);
}

void Renderer::setRenderLights(bool b)
{
	shouldRenderLights = b;	
}

Model* 
Renderer::loadModel(char* obj_path, char* bmp_path)
{
	Model* temp = new Model(obj_path, bmp_path);
	models.push_back(temp);
	return(temp);
}