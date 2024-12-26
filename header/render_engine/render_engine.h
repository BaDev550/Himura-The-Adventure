#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class RenderEngine
{
public:
	GLFWwindow* window;

	RenderEngine() {};

	void StartRendering();
protected:
	GLsizei win_height = 800, win_width = 800;
private:
	bool InitilizeWindow();
	bool MainRendering();
};