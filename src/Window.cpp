#include "Window.h"

//#define NO_CONTROL 

inline void 
framebuffer_size_callback(GLFWwindow* window, int32 width, int32 height)
{
	glViewport(0, 0, width, height);
}

inline void
error_callback(int32 error, const char* description)
{
	print("GLFW HAS ENCOUNTERED AN ERROR::" << error << "::" << description);
}

Window::Window(uint32 width, uint32 height, char* title)
{
	// TODO(dallas): Do something other than exit(-1) here
	if (!glfwInit()) { print("Error initializing GLFW"); pause(); exit(-1); }

	window = glfwCreateWindow(width, height, title, 0, 0);
	if (!window) { print("Error creating GLFW window"); pause(); exit(-1); }

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(error_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	uint16 w = 16;
	uint16 h = 16;
	unsigned char* pixels = new unsigned char[(w*h)*4];

	for (int i = 0; i < (w*h) * 4; i++)
		pixels[i] = 0x00;
	
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			uint8 r = rand() % 256;
			uint8 g = rand() % 256;
			uint8 b = rand() % 256;

			// This was hard to understand. Look into it
			pixels[y * 64 + x * 4 + 0] = r;
			pixels[y * 64 + x * 4 + 1] = g;
			pixels[y * 64 + x * 4 + 2] = b;
			pixels[y * 64 + x * 4 + 3] = 0x00;
		}
	GLFWimage image;
	image.height = 16;
	image.width = 16;
	image.pixels = &pixels[0];
	//glfwSetWindowIcon(WINDOW, 1, &image);**********************************What the hell

// Good demonstration of what happens if you use 8 bit values for OpenGL color methods instead of float clamps
#if 1
	real32 r = (real32)((BACKGROUND_COLOR & 0xff000000) >> 24) / 256.0f;
	real32 g = (real32)((BACKGROUND_COLOR & 0x00ff0000) >> 16) / 256.0f;
	real32 b = (real32)((BACKGROUND_COLOR & 0x0000ff00) >> 8) / 256.0f;
#else
	uint8 r = (BACKGROUND_COLOR & 0xff000000) >> 24;
	uint8 g = (BACKGROUND_COLOR & 0x00ff0000) >> 16;
	uint8 b = (BACKGROUND_COLOR & 0x0000ff00) >> 8;
#endif
	glClearColor(r, g, b, 0);

	delete[] pixels;

	//			 What the hell VS ?
	if (glewInit() != GLEW_OK) { print("Error initializing GLEW"); pause(); exit(-1); }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Window::~Window()
{
	close();
}

GLFWwindow*
Window::getWindow()
{
	return(window);
}

bool 
Window::isOpen()
{
	return(!glfwWindowShouldClose(window));
}

void
Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Window::update(Camera *camera, Light* light)
{
	updateKeys(camera, light);
	updateCursor(camera);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Crashes GLFW if not passed by a pointer? Weird
void 
Window::updateKeys(Camera* camera, Light* light)
{
#ifndef NO_CONTROL
	keys[KEY_W] = glfwGetKey(window, GLFW_KEY_W);
	keys[KEY_A] = glfwGetKey(window, GLFW_KEY_A);
	keys[KEY_S] = glfwGetKey(window, GLFW_KEY_S);
	keys[KEY_D] = glfwGetKey(window, GLFW_KEY_D);
	keys[KEY_E] = glfwGetKey(window, GLFW_KEY_E);
	keys[KEY_Q] = glfwGetKey(window, GLFW_KEY_Q);
	keys[KEY_UP] = glfwGetKey(window, GLFW_KEY_UP);
	keys[KEY_LEFT] = glfwGetKey(window, GLFW_KEY_LEFT);
	keys[KEY_DOWN] = glfwGetKey(window, GLFW_KEY_DOWN);
	keys[KEY_RIGHT] = glfwGetKey(window, GLFW_KEY_RIGHT);
	keys[KEY_NUMPAD_0] = glfwGetKey(window, GLFW_KEY_KP_0);
	keys[KEY_NUMPAD_1] = glfwGetKey(window, GLFW_KEY_KP_1);
	keys[KEY_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
//#define SINGLE_PRESS
#ifdef SINGLE_PRESS
	// Input for single press
	if(keys[KEY_W] == GLFW_PRESS && !key_was_pressed[KEY_W])
	{
		key_was_pressed[KEY_W] = true;
		camera->translation += camera->rotation * MOVE_SPEED;
	}
	else if(keys[KEY_W] == GLFW_RELEASE) key_was_pressed[KEY_W] = false;
	if(keys[KEY_A] == GLFW_PRESS && !key_was_pressed[KEY_A])
	{
		key_was_pressed[KEY_A] = true;
		camera->translation -= camera->right * MOVE_SPEED;
	}
	else if(keys[KEY_A] == GLFW_RELEASE) key_was_pressed[KEY_A] = false;
	if(keys[KEY_S] == GLFW_PRESS && !key_was_pressed[KEY_S])
	{
		key_was_pressed[KEY_S] = true;
		camera->translation -= camera->rotation * MOVE_SPEED;
	}
	else if(keys[KEY_S] == GLFW_RELEASE) key_was_pressed[KEY_S] = false;
	if(keys[KEY_D] == GLFW_PRESS && !key_was_pressed[KEY_D])
	{
		key_was_pressed[KEY_D] = true;
		camera->translation += camera->right * MOVE_SPEED;
	}
	else if(keys[KEY_D] == GLFW_RELEASE) key_was_pressed[KEY_D] = false;
	if(keys[KEY_E] == GLFW_PRESS && !key_was_pressed[KEY_E])
	{
		key_was_pressed[KEY_E] = true;
		camera->translation.y += MOVE_SPEED;
	}
	else if(keys[KEY_E] == GLFW_RELEASE) key_was_pressed[KEY_E] = false;
	if(keys[KEY_Q] == GLFW_PRESS && !key_was_pressed[KEY_Q])
	{
		key_was_pressed[KEY_Q] = true;
		camera->translation.y -= MOVE_SPEED;
	}
	else if(keys[KEY_Q] == GLFW_RELEASE) key_was_pressed[KEY_Q] = false;
	if(keys[KEY_UP] == GLFW_PRESS && !key_was_pressed[KEY_UP])
	{
		key_was_pressed[KEY_UP] = true;
		light->translation.z -= MOVE_SPEED;
	}
	else if(keys[KEY_UP] == GLFW_RELEASE) key_was_pressed[KEY_UP] = false;
	if(keys[KEY_LEFT] == GLFW_PRESS && !key_was_pressed[KEY_LEFT])
	{
		key_was_pressed[KEY_LEFT] = true;
		light->translation.x -= MOVE_SPEED;
	}
	else if(keys[KEY_LEFT] == GLFW_RELEASE) key_was_pressed[KEY_LEFT] = false;
	if(keys[KEY_DOWN] == GLFW_PRESS && !key_was_pressed[KEY_DOWN])
	{
		key_was_pressed[KEY_DOWN] = true;
		light->translation.z += MOVE_SPEED;
	}
	else if(keys[KEY_DOWN] == GLFW_RELEASE) key_was_pressed[KEY_DOWN] = false;
	if(keys[KEY_RIGHT] == GLFW_PRESS && !key_was_pressed[KEY_RIGHT])
	{
		key_was_pressed[KEY_RIGHT] = true;
		light->translation.x += MOVE_SPEED;
	}
	else if(keys[KEY_RIGHT] == GLFW_RELEASE) key_was_pressed[KEY_RIGHT] = false;
	if(keys[KEY_NUMPAD_0] == GLFW_PRESS && !key_was_pressed[KEY_NUMPAD_0])
	{
		key_was_pressed[KEY_NUMPAD_0] = true;
		light->translation.y -= MOVE_SPEED;
	}
	else if(keys[KEY_NUMPAD_0] == GLFW_RELEASE) key_was_pressed[KEY_NUMPAD_0] = false;
	if(keys[KEY_NUMPAD_1] == GLFW_PRESS && !key_was_pressed[KEY_NUMPAD_1])
	{
		key_was_pressed[KEY_NUMPAD_1] = true;
		light->translation.y += MOVE_SPEED;
	}
	else if(keys[KEY_NUMPAD_1] == GLFW_RELEASE) key_was_pressed[KEY_NUMPAD_1] = false;
#else
	if(keys[KEY_W] == GLFW_PRESS)
	{
		key_was_pressed[KEY_W] = true;
		camera->translation += camera->rotation * MOVE_SPEED;
	}
	else if(keys[KEY_W] == GLFW_RELEASE) key_was_pressed[KEY_W] = false;
	if(keys[KEY_A] == GLFW_PRESS)
	{
		key_was_pressed[KEY_A] = true;
		camera->translation -= camera->right * MOVE_SPEED;
	}
	else if(keys[KEY_A] == GLFW_RELEASE) key_was_pressed[KEY_A] = false;
	if(keys[KEY_S] == GLFW_PRESS)
	{
		key_was_pressed[KEY_S] = true;
		camera->translation -= camera->rotation * MOVE_SPEED;
	}
	else if(keys[KEY_S] == GLFW_RELEASE) key_was_pressed[KEY_S] = false;
	if(keys[KEY_D] == GLFW_PRESS)
	{
		key_was_pressed[KEY_D] = true;
		camera->translation += camera->right * MOVE_SPEED;
	}
	else if(keys[KEY_D] == GLFW_RELEASE) key_was_pressed[KEY_D] = false;
	if(keys[KEY_E] == GLFW_PRESS)
	{
		key_was_pressed[KEY_E] = true;
		camera->translation.y += MOVE_SPEED;
	}
	else if(keys[KEY_E] == GLFW_RELEASE) key_was_pressed[KEY_E] = false;
	if(keys[KEY_Q] == GLFW_PRESS)
	{
		key_was_pressed[KEY_Q] = true;
		camera->translation.y -= MOVE_SPEED;
	}
	else if(keys[KEY_Q] == GLFW_RELEASE) key_was_pressed[KEY_Q] = false;
	if(keys[KEY_UP] == GLFW_PRESS)
	{
		key_was_pressed[KEY_UP] = true;
		light->translation.z -= MOVE_SPEED;
	}
	else if(keys[KEY_UP] == GLFW_RELEASE) key_was_pressed[KEY_UP] = false;
	if(keys[KEY_LEFT] == GLFW_PRESS)
	{
		key_was_pressed[KEY_LEFT] = true;
		light->translation.x -= MOVE_SPEED;
	}
	else if(keys[KEY_LEFT] == GLFW_RELEASE) key_was_pressed[KEY_LEFT] = false;
	if(keys[KEY_DOWN] == GLFW_PRESS)
	{
		key_was_pressed[KEY_DOWN] = true;
		light->translation.z += MOVE_SPEED;
	}
	else if(keys[KEY_DOWN] == GLFW_RELEASE) key_was_pressed[KEY_DOWN] = false;
	if(keys[KEY_RIGHT] == GLFW_PRESS)
	{
		key_was_pressed[KEY_RIGHT] = true;
		light->translation.x += MOVE_SPEED;
	}
	else if(keys[KEY_RIGHT] == GLFW_RELEASE) key_was_pressed[KEY_RIGHT] = false;
	if(keys[KEY_NUMPAD_0] == GLFW_PRESS)
	{
		key_was_pressed[KEY_NUMPAD_0] = true;
		light->translation.y -= MOVE_SPEED;
	}
	else if(keys[KEY_NUMPAD_0] == GLFW_RELEASE) key_was_pressed[KEY_NUMPAD_0] = false;
	if(keys[KEY_NUMPAD_1] == GLFW_PRESS)
	{
		key_was_pressed[KEY_NUMPAD_1] = true;
		light->translation.y += MOVE_SPEED;
	}
	else if(keys[KEY_NUMPAD_1] == GLFW_RELEASE) key_was_pressed[KEY_NUMPAD_1] = false;
#endif
#endif
}

static real64 lastMouseX = 0, lastMouseY = 0;
void
Window::updateCursor(Camera* camera)
{
#ifndef NO_CONTROL
	real64 xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	real64 deltaX = xpos - lastMouseX;
	real64 deltaY = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	if (fabs(deltaX) > MAX_MOUSE_DELTA_X || fabs(deltaY) > MAX_MOUSE_DELTA_Y)
	{
		print("------------TOO FAST------------\nxpos: " << xpos << ", ypos: " << ypos << "\tdeltaX: " << deltaX << ", deltaY: " << deltaY);
		return;
	}

	camera->rotation = glm::mat3(glm::rotate(-(real32)deltaX / MOUSE_SMOOTHING_X, camera->UP)) * camera->rotation;
	camera->right = glm::cross(camera->rotation, camera->UP);
	camera->rotation = glm::mat3(glm::rotate(+(real32)deltaY / MOUSE_SMOOTHING_Y, camera->right)) * camera->rotation;

/* Switch
	print("Camera position: (" << camera->translation.x << ", " << camera->translation.y << ", " << camera->translation.z << ")"
		<<" Camera rotation: (" << camera->rotation.x << ", " << camera->rotation.y << ", " << camera->rotation.z << ")"
		<<" Camera scale: " << camera->scale);
*/

/* Switch
	print("Camera position: (" << camera->translation.x << ", " << camera->translation.y << ", " << camera->translation.z << ")"
		<< " Camera UP: (" << camera->UP.x << ", " << camera->UP.y << ", " << camera->UP.z << ")"
		<< " Camera right: (" << camera->right.x << ", " << camera->right.y << ", " << camera->right.z << ")");
*/

#endif
}

void
Window::close()
{
	glfwTerminate();
}