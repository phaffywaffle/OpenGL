#include "defines.h"

#include "Window.h"
#include "PassthroughShader.h"
#include "Model.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"

int
main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "This is the start of a new day");
	Camera camera(glm::vec3(0,0,0));

	PassthroughShader shader;

	Light light;
	light.scale = 0.07;
	Renderer renderer(&shader, &camera, &light);


	print("Loading cube.obj...");
	Model cube("cube.obj");
	print("done");

	Entity e(cube, glm::vec3(0,0,-10));
	renderer.addEntity(e);

	Entity f(cube, glm::vec3(0,0,0));
	renderer.addEntity(f);
	Entity g(cube, glm::vec3(0,5,0));
	renderer.addEntity(g);
	Entity h(cube, glm::vec3(0,0,-4), glm::vec3(12,74,52), 0.2f);
	renderer.addEntity(h);

	while (window.isOpen())
	{
		window.clear();
		
		renderer.render();
		
		window.update(&camera, &light);
	}

	return(0);
}