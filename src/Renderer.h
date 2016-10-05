/*
	The problem with this renderer is it assumes all the Entity pointers given to it 
	share the same Model pointer. This means if different entities are created, and 
	their model pointers point to different model objects with the same vertex data, 
	two different entries will be created in the map, defeating the whole purpose 
	of the optimization.
*/

#pragma once

#include "defines.h"
#include "Shader.h"
#include "PassthroughShader.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"

typedef std::map<Model*,std::vector<Entity*>*> map_type;

class Renderer
{
public:
	static glm::mat4 pr_matrix;
private:
	static glm::mat4 vw_matrix;
	static glm::mat4 tr_matrix;
	static glm::mat4 rt_matrix;
	static glm::mat4 sc_matrix;
	std::vector<Model*> models;
	map_type entityMap;
	PassthroughShader passthrough_shader;
	Camera* camera;
	Light* light;
	static bool shouldRenderLights;
public:
	Renderer(Camera*,Light*);
	// Fix
	//static inline glm::mat4 getProjectionMatrix() { return(pr_matrix); }
	void render();
	void renderEntities();
	void renderLights();
	// Maybe take in as a pointer?
	void addEntity(Entity*);
	uint32 numEntites(Model*);
	void setRenderLights(bool);
	Model* loadModel(char*,char*);
	// Returns 0 if no model is found
	Model* modelPointer(Model*);
};