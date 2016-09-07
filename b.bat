@echo off

cl /EHsc /I F:\OpenGL\GLEW\include /I F:\OpenGL\GLFW\include /I F:\OpenGL\GLM test.cpp glew32.lib glfw3dll.lib opengl32.lib