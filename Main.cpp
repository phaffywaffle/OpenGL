#include "defines.h"

#include "Model.h"

global GLFWwindow* WINDOW;
global char* TITLE = "GLFW Window";

/* SHADERS & LOCATIONS */
GLuint programID;
GLuint location_pr_matrix;
GLuint location_vw_matrix;
GLuint location_ml_matrix;
GLuint location_tr_matrix;
GLuint location_rt_matrix;
GLuint location_sc_matrix;
GLuint location_shade_normals;
GLuint location_shade_light;
GLuint location_ambient_light_factor;
GLuint location_light_position;
GLuint location_eye_position;

/* MATRICES & VARIABLES */
global glm::mat4 id = glm::mat4();

global glm::mat4 pr_matrix;
// in RADIANS
global real32 fov = 1.047197f;
global real32 aspectRatio = ((real32)WIDTH / (real32)HEIGHT);
global real32 nearPlane = 0.1f;
global real32 farPlane = 100.0f;

global glm::mat4 vw_matrix;
global glm::vec3 eyePosition = glm::vec3(0, 0, 0);
// Maybe shouldn't be normalized?
global glm::vec3 lookDirection = glm::normalize(glm::vec3(0,0,-1));
global glm::vec3 up = glm::vec3(0, 1, 0);
global glm::vec3 right = glm::cross(up, lookDirection);

global glm::mat4 tr_matrix;
global glm::vec3 translation = glm::vec3(0.0f, 0.0f, -10.0f);
global glm::mat4 rt_matrix;
global float ZERO_ROTATION = 0.0f; // fix this
global real32 rotX = 0.0f;
global real32 rotY = 0.0f;
global real32 rotZ = 0.0f;
global glm::vec3 xaxis = glm::vec3(1,0,0);
global glm::vec3 yaxis = glm::vec3(0,1,0);
global glm::vec3 zaxis = glm::vec3(0,0,1);
global glm::mat4 sc_matrix;
global real32 scaleFactor = 3.0f;

global real32 shadeNormals = GLSL_TRUE;
global real32 shadeLight = GLSL_FALSE;

global real32 ambientLightFactor = 0.2f;

glm::vec3 ORIGINAL_LIGHT_POSITION = glm::vec3(0.0f, 0.0f, -4.0f); // fix this

global glm::vec3 lightPosition = ORIGINAL_LIGHT_POSITION;
global float ORIGINAL_LIGHT_SCALE = 0.07f;
float lightScale = ORIGINAL_LIGHT_SCALE;
glm::mat4 light_tr_matrix = glm::translate(lightPosition);
global glm::mat4 light_sc_matrix = glm::scale(glm::vec3(lightScale, lightScale, lightScale));

/* PROTOTYPES */
internal void swapBuffers();

/* CALLBACKS */
internal void
error_callback(int error, const char* description)
{
	std::cout << "GLFW HAS ENCOUNTERED AN ERROR: " << error << std::endl;
}

internal void 
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

internal void
resetModels()
{
	rotX = ZERO_ROTATION;
	rotY = ZERO_ROTATION;
	rotZ = ZERO_ROTATION;

	lightPosition = ORIGINAL_LIGHT_POSITION;
	lightScale = ORIGINAL_LIGHT_SCALE;
}

global real64 increment = 1.0;
internal void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_D)	eyePosition -= MOVE_SPEED * right;
	if (key == GLFW_KEY_A)	eyePosition += MOVE_SPEED * right;
	if (key == GLFW_KEY_W)	eyePosition += MOVE_SPEED * lookDirection;
	if (key == GLFW_KEY_S)	eyePosition -= MOVE_SPEED * lookDirection;
	if (key == GLFW_KEY_E)	eyePosition += MOVE_SPEED * up;
	if (key == GLFW_KEY_Q)	eyePosition -= MOVE_SPEED * up;
	if (key == GLFW_KEY_KP_8)	rotX -= 0.1f;
	if (key == GLFW_KEY_KP_2)	rotX += 0.1f;
	if (key == GLFW_KEY_KP_4)	rotY -= 0.1f;
	if (key == GLFW_KEY_KP_6)	rotY += 0.1f;
	if (key == GLFW_KEY_KP_7)	rotZ += 0.1f;
	if (key == GLFW_KEY_KP_9)	rotZ -= 0.1f;
	if (key == GLFW_KEY_RIGHT)	lightPosition.x += 0.25f;
	if (key == GLFW_KEY_LEFT)	lightPosition.x -= 0.25f;
	if (key == GLFW_KEY_DOWN)	lightPosition.z += 0.25f;
	if (key == GLFW_KEY_UP)		lightPosition.z -= 0.25f;
	if (key == GLFW_KEY_KP_1)	lightPosition.y += 0.25f;
	if (key == GLFW_KEY_KP_0)	lightPosition.y -= 0.25f;
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)	shadeNormals *= -1.0f;
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) shadeLight *= -1.0f;
	if (key == GLFW_KEY_LEFT_BRACKET)	lightScale -= 0.1f;
	if (key == GLFW_KEY_RIGHT_BRACKET)	lightScale += 0.1f;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) resetModels();
}

internal void 
mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{}

global real64 lastMouseX = 0;
global real64 lastMouseY = 0;
global float invertedX = -1;
global float invertedY = -1;
internal void 
cursor_position_callback(GLFWwindow* window, real64 xpos, real64 ypos)
{
	// Because of how GLFW works, this needs to be like this if you want a positive deltaX to mean cursor right
	real64 deltaX = xpos - lastMouseX;
	real64 deltaY = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	if (fabs(deltaX) > MAX_MOUSE_DELTA_X || fabs(deltaY) > MAX_MOUSE_DELTA_Y)
	{
		print("------------TOO FAST------------\nxpos: " << xpos << ", ypos: " << ypos << "\tdeltaX: " << deltaX << ", deltaY: " << deltaY);
		return;
	}

	lookDirection = glm::mat3(glm::rotate((real32)deltaX * invertedX / MOUSE_SMOOTHING_X, up)) * lookDirection;
	// Be sure to cross here
	right = glm::cross(up, lookDirection);
	lookDirection = glm::mat3(glm::rotate((real32)deltaY * invertedY / MOUSE_SMOOTHING_Y, right)) * lookDirection;
}

/* FUNCTIONS */
internal void
checkShaderCompile(GLuint shader, GLint type)
{
	GLint compileStatus;
	GLint infoLength;
	GLchar* buffer = {};

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		buffer = new GLchar[infoLength];
		// Might throw error
		glGetShaderInfoLog(shader, infoLength, 0, buffer);
		if (type == GL_VERTEX_SHADER) std::cout << "Errors in vertex shader: " << buffer << std::endl;
		else if (type == GL_FRAGMENT_SHADER) std::cout << "Errors in fragment shader: " << buffer << std::endl;
	}

	delete[] buffer;
}

bool
checkProgramStatus(GLuint program)
{
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		GLchar* buffer = new GLchar[infoLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(program, infoLength, &bufferSize, buffer);
		std::cout << "Error linking program: " << buffer << std::endl;
		delete[] buffer;
		return(false);
	}
	return(true);
}

internal std::string
readShaderCode(char* filename)
{
	std::ifstream input(filename);
	if (!input.good())
	{
		print("File " << filename << " failed to load.");
		exit(-1);
	}

	return(std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>()));
}

internal GLuint
createProgram()
{
	GLuint program = glCreateProgram();
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VSCString = readShaderCode("vertex.shader");
	std::string FSCString = readShaderCode("fragment.shader");
	const char* vertexShaderCode = VSCString.c_str();
	const char* fragmentShaderCode = FSCString.c_str();

	glShaderSource(vertShader, 1, &vertexShaderCode, 0);
	glShaderSource(fragShader, 1, &fragmentShaderCode, 0);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	checkShaderCompile(vertShader, GL_VERTEX_SHADER);
	checkShaderCompile(fragShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);
	if (checkProgramStatus(program)) glUseProgram(program);
	else { print("Program not okay !"); system("PAUSE"); exit(-1); }

	location_pr_matrix = glGetUniformLocation(program, "pr_matrix");
	location_vw_matrix = glGetUniformLocation(program, "vw_matrix");
	location_tr_matrix = glGetUniformLocation(program, "tr_matrix");
	location_rt_matrix = glGetUniformLocation(program, "rt_matrix");
	location_sc_matrix = glGetUniformLocation(program, "sc_matrix");
	location_shade_normals = glGetUniformLocation(program, "shadeNormals");
	location_shade_light = glGetUniformLocation(program, "shadeLight");
	location_ambient_light_factor = glGetUniformLocation(program, "ambientLightFactor");
	location_light_position = glGetUniformLocation(program, "lightPosition");
	location_eye_position = glGetUniformLocation(program, "eyePosition");

//#define CHECK_ALL_UNIFORMS
#ifdef CHECK_ALL_UNIFORMS
	if (location_pr_matrix == -1 || location_vw_matrix == -1 || location_tr_matrix == -1 || location_rt_matrix == -1 || location_sc_matrix == -1
		|| location_ambient_light_factor == -1 || location_shade_normals == -1 || location_light_position == -1)
	{
		print("Not all uniforms found!");
		system("PAUSE");
		exit(-1);
	}
#endif
	return(program);
}

internal void
updateMatrices()
{
	pr_matrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	/* This fucked me up for a long time and I'm still not sure I understand it too well */
	vw_matrix = glm::lookAt(eyePosition, eyePosition + lookDirection, up);
	tr_matrix = glm::translate(translation);
	rt_matrix = glm::rotate(rotX, xaxis) * glm::rotate(rotY, yaxis) * glm::rotate(rotZ, zaxis);
	sc_matrix = glm::scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	light_tr_matrix = glm::translate(lightPosition);
	light_sc_matrix = glm::scale(glm::vec3(lightScale, lightScale, lightScale));
}

internal void
// Crashes if this isn't a pointer or by reference.
// If this is isn't one of those, a new Model object is created and destroyed when the method exits calling a premature destructor and corrupting the heap 
sendToGPU(Model* m)
{
	glBindVertexArray(m->vao);

	glUniformMatrix4fv(location_pr_matrix, 1, GL_FALSE, &pr_matrix[0][0]);
	glUniformMatrix4fv(location_vw_matrix, 1, GL_FALSE, &vw_matrix[0][0]);
	glUniformMatrix4fv(location_tr_matrix, 1, GL_FALSE, &tr_matrix[0][0]);
	glUniformMatrix4fv(location_rt_matrix, 1, GL_FALSE, &rt_matrix[0][0]);
	glUniformMatrix4fv(location_sc_matrix, 1, GL_FALSE, &sc_matrix[0][0]);
	glUniform1fv(location_shade_normals, 1, &shadeNormals);
	glUniform1fv(location_shade_light, 1, &shadeLight);
	glUniform1fv(location_ambient_light_factor, 1, &ambientLightFactor);
	glUniform3fv(location_light_position, 1, &lightPosition[0]);
	glUniform3fv(location_eye_position, 1, &eyePosition[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLushort), m->indices, GL_STATIC_DRAW);//

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Initializer / Closer */
internal void
init()
{
	// TODO(dallas): Do something other than exit(-1) here
	if (!glfwInit()) { std::cout << "Error initializing GLFW" << std::endl; exit(-1); }

	WINDOW = glfwCreateWindow(WIDTH, HEIGHT, TITLE, 0, 0);
	if (!WINDOW) { std::cout << "Error creating GLFW window" << std::endl; exit(-1); }

	glfwMakeContextCurrent(WINDOW);
	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(WINDOW, framebuffer_size_callback);
	glfwSetKeyCallback(WINDOW, key_callback);
	glfwSetMouseButtonCallback(WINDOW, mouse_button_callback);
	glfwSetCursorPosCallback(WINDOW, cursor_position_callback);
	// For mouse input
	glfwSetInputMode(WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

			// This was incredibly hard to understand. Look into it
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
	if (glewInit() != GLEW_OK) { std::cout << "Error initializing GLEW" << std::endl; exit(-1); }

	glEnable(GL_DEPTH_TEST);
	// Later
	//glEnable(GL_CULL_FACE);

	programID = createProgram();

	updateMatrices();
}

// Probably useless
internal void
close()
{
	glfwTerminate();
}

/* MAIN */
int
main()
{
	init();

	Model m;

	while (!glfwWindowShouldClose(WINDOW))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateMatrices();
		sendToGPU(&m);
	
		m.bind();

		glDrawElements(GL_TRIANGLES, m.num_indices, GL_UNSIGNED_SHORT, 0);

		glUniformMatrix4fv(location_pr_matrix, 1, GL_FALSE, &pr_matrix[0][0]);
		glUniformMatrix4fv(location_vw_matrix, 1, GL_FALSE, &vw_matrix[0][0]);
		glUniformMatrix4fv(location_tr_matrix, 1, GL_FALSE, &light_tr_matrix[0][0]);
		glUniformMatrix4fv(location_rt_matrix, 1, GL_FALSE, &id[0][0]);
		glUniformMatrix4fv(location_sc_matrix, 1, GL_FALSE, &light_sc_matrix[0][0]);
		glUniform1fv(location_shade_normals, 1, &shadeNormals);
		glUniform1fv(location_shade_light, 1, &shadeLight);
		glUniform1fv(location_ambient_light_factor, 1, &ambientLightFactor);
		glUniform3fv(location_light_position, 1, &lightPosition[0]);
		glUniform3fv(location_eye_position, 1, &eyePosition[0]);
		glDrawElements(GL_TRIANGLES, m.num_indices, GL_UNSIGNED_SHORT, 0);
		
		glfwSwapBuffers(WINDOW);
		glfwPollEvents();
	}

	return(0);
}