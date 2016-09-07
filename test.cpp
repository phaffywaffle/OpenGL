#pragma once

#include <iostream>	
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>

int
main()
{
	glewInit();

	glfwInit();

	std::cout << "The test works!" << std::endl;
	system("PAUSE");

	return(0);
}