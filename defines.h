#pragma once

#include <iostream>	
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory.h>
#include <iostream>
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define internal static
#define global static

#define print(x) std::cout << x << std::endl
#define pause() system("PAUSE")
#define NUM_ARRAY_ELEMENTS(x) sizeof(x) / sizeof(*x)

#define WINDOW_WIDTH 1028
#define WINDOW_HEIGHT 720
#define BACKGROUND_COLOR 0x01234567

#define FOV 1.047197f
#define ASPECT_RATIO ((real32)WINDOW_WIDTH / (real32)WINDOW_HEIGHT)
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

#define PI 3.141592f

#define MAX_MOUSE_DELTA_X 520
#define MAX_MOUSE_DELTA_Y 520
#define MOUSE_SMOOTHING_X 300
#define MOUSE_SMOOTHING_Y 300
#define MOUSE_X_INVERTED -1
#define MOUSE_X_NOT_INVERTED 1
#define MOUSE_Y_INVERTED -1
#define MOUSE_Y_NOT_INVERTED 1

#define MOVE_SPEED 0.25f

#define GLSL_TRUE 1.0f
#define GLSL_FALSE -1.0f

#define FLOATS_PER_VERTEX 3
#define FLOATS_PER_UV 2
#define FLOATS_PER_NORMAL 3

#define X_AXIS glm::vec3(1.0f,0.0f,0.0f)
#define Y_AXIS glm::vec3(0.0f,1.0f,0.0f)
#define Z_AXIS glm::vec3(0.0f,0.0f,1.0f)

#define ZERO_ROTATION 0.0f // fix this (?)

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