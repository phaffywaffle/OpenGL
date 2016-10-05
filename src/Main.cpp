#include "defines.h"

#include "Window.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"

int
main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Window");
	Camera camera;
	Light light;
	Renderer renderer(&camera, &light);
	renderer.setRenderLights(true);
	// Right now we can't create and Entity without first loading a model manually
	// This is nice cause all the Entities can use the same Model object, saving space
	// This is not nice cause now we have to specify each model we want to use explicitly
	// In the future maybe the rendere could do this on its own?
	Model* cube = renderer.loadModel("res/cube.obj", "res/red_blue_gradient.bmp");

	light.model = cube;

	std::vector<Entity*> entities;


	for(uint32 i = 0; i < 1000; i++)
	{
		float x = (float)(rand() % 50) - 25.0f;
		float y = (float)(rand() % 50) - 25.0f;
		float z = (float)(rand() % 50) - 25.0f;

		float rx = (float)(rand() % 50) - 25.0f;
		float ry = (float)(rand() % 50) - 25.0f;
		float rz = (float)(rand() % 50) - 25.0f;

		Entity* temp = new Entity(cube, glm::vec3(x,y,z), glm::vec3(rx,ry,rz), 0.4f);
		entities.push_back(temp);
		renderer.addEntity(entities.at(i));
	}
	
	while (window.isOpen())
	{
		window.clear();
		
		renderer.render();
		
		window.update(&camera, &light);
	}

	return(0);
}