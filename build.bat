@echo off

if exist Main.exe del Main.exe else echo No existing .exe to be deleted

c++ Main.cpp Model.cpp -w -o Main -I x:\flash\OpenGL\GLEW\include -I x:\flash\OpenGL\GLFW\include -I x:\flash\OpenGL\GLM  -lglew32 -lglfw3 -lopengl32 -lgdi32