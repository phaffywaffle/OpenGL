#include "Renderer.h"

glm::mat4 Renderer::pr_matrix = glm::perspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
glm::mat4 Renderer::vw_matrix = glm::mat4();
glm::mat4 Renderer::tr_matrix = glm::mat4();
glm::mat4 Renderer::rt_matrix = glm::mat4();
glm::mat4 Renderer::sc_matrix = glm::mat4();

Renderer::Renderer(PassthroughShader* _shader, Camera* _camera, Light* _light)
	:	shader(_shader), camera(_camera), light(_light)
{}
void
Renderer::render()
{
	if(entities.size() != 0)
		// Can't use for:each loop here which is pretty annoying
		for(uint32 i = 0; i < entities.size(); i++)
			renderEntity(entities.at(i));
	else print("No entities to render");
	renderLights();
}

void
Renderer::renderEntity(Entity e)
{
	shader->enable();
	e.getModel().bind();
	vw_matrix = camera->getViewMatrix();
	tr_matrix = glm::translate(e.translation);
	rt_matrix = glm::rotate(e.rotation.x, X_AXIS) * glm::rotate(e.rotation.y, Y_AXIS) * glm::rotate(e.rotation.z, Z_AXIS);
	sc_matrix = glm::scale(glm::vec3(e.scale,e.scale,e.scale));
	glUniformMatrix4fv(shader->get_location_pr_matrix(), 1, GL_FALSE, &pr_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_vw_matrix(), 1, GL_FALSE, &vw_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_tr_matrix(), 1, GL_FALSE, &tr_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_rt_matrix(), 1, GL_FALSE, &rt_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_sc_matrix(), 1, GL_FALSE, &sc_matrix[0][0]);
	glUniform1fv(shader->get_location_ambient_light_factor(), 1, &shader->ambientLightFactor);
	tr_matrix = glm::translate(e.translation);
	sc_matrix = glm::scale(glm::vec3(e.scale,e.scale,e.scale));
	glUniform3fv(shader->get_location_light_position(), 1, &light->translation[0]);
	glUniform3fv(shader->get_location_eye_position(), 1, &camera->translation[0]);
	glDrawArrays(GL_TRIANGLES, 0, FLOATS_PER_VERTEX * e.getModel().vertCount());
	e.getModel().unbind();
	shader->disable();
}

void
Renderer::renderLights()
{
	shader->enable();
	light->getModel().bind();
	vw_matrix = camera->getViewMatrix();
	tr_matrix = glm::translate(light->translation);
	rt_matrix = glm::rotate(light->rotation.x, X_AXIS) * glm::rotate(light->rotation.y, Y_AXIS) * glm::rotate(light->rotation.z, Z_AXIS);
	sc_matrix = glm::scale(glm::vec3(light->scale,light->scale,light->scale));
	glUniformMatrix4fv(shader->get_location_pr_matrix(), 1, GL_FALSE, &pr_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_vw_matrix(), 1, GL_FALSE, &vw_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_tr_matrix(), 1, GL_FALSE, &tr_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_rt_matrix(), 1, GL_FALSE, &rt_matrix[0][0]);
	glUniformMatrix4fv(shader->get_location_sc_matrix(), 1, GL_FALSE, &sc_matrix[0][0]);
	glUniform1fv(shader->get_location_ambient_light_factor(), 1, &shader->ambientLightFactor);
	tr_matrix = glm::translate(light->translation);
	sc_matrix = glm::scale(glm::vec3(light->scale,light->scale,light->scale));
	glUniform3fv(shader->get_location_light_position(), 1, &light->translation[0]);
	glUniform3fv(shader->get_location_eye_position(), 1, &camera->translation[0]);
	glDrawArrays(GL_TRIANGLES, 0, FLOATS_PER_VERTEX * light->getModel().vertCount());
	light->getModel().unbind();
	shader->disable();
}

void
Renderer::addEntity(Entity e)
{
	entities.push_back(e);
}