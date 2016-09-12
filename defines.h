#pragma once

#include <iostream>	
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>

#define internal static
#define global static

#define print(x) std::cout << x << std::endl
#define pause() system("PAUSE")
#define NUM_ARRAY_ELEMENTS(x) sizeof(x) / sizeof(*x)

#define WIDTH 1028
#define HEIGHT 720
#define BACKGROUND_COLOR 0x01234567

#define PI 3.141592f

#define MAX_MOUSE_DELTA_X 520
#define MAX_MOUSE_DELTA_Y 520
#define MOUSE_SMOOTHING_X 400
#define MOUSE_SMOOTHING_Y 400

#define MOVE_SPEED 0.25f

#define GLSL_TRUE 1.0f
#define GLSL_FALSE -1.0f

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;