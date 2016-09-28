#pragma once

#include "defines.h"
#include "PassthroughShader.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"

class Renderer
{
public:
	static glm::mat4 pr_matrix;
private:
	static glm::mat4 vw_matrix;
	static glm::mat4 tr_matrix;
	static glm::mat4 rt_matrix;
	static glm::mat4 sc_matrix;
	std::vector<Entity> entities;
	PassthroughShader* shader;
	Camera* camera;
	Light* light;
public:
	Renderer(PassthroughShader*,Camera*,Light*);
	// Fix
	//static inline glm::mat4 getProjectionMatrix() { return(pr_matrix); }
	void render();
	// Maybe take in as a pointer?
	void renderEntity(Entity);
	void renderLights();
	// Maybe take in as a pointer?
	void addEntity(Entity);
};