@echo off

c++ Main.cpp Model.cpp -o Main -I x:\flash\OpenGL\GLEW\include -I x:\flash\OpenGL\GLFW\include -I x:\flash\OpenGL\GLM -DGLEW_STATIC glew32s.lib -lglfw3 -lopengl32 -luser32 -lkernel32 -lgdi32