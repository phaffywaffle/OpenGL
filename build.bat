@echo off

if exist Main.exe del Main.exe else echo No existing .exe to be deleted

c++ src\Main.cpp src\Window.cpp src\Model.cpp src\Shader.cpp src\PassthroughShader.cpp src\Entity.cpp src\Camera.cpp src\Light.cpp src\Renderer.cpp -w -o Main -I x:\flash\OpenGL\GLEW\include -I x:\flash\OpenGL\GLFW\include -I x:\flash\OpenGL\GLM  -lglew32 -lglfw3 -lopengl32 -lgdi32
