#ifndef RENDER_ENGINE_HEADER_CLASS
#define RENDER_ENGINE_HEADER_CLASS
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <game_engine.h>

class RenderEngine
{
public:
	GLFWwindow* window;
	GameEngine* BAXGameEngine;
	float deltaTime = 0.0f;

	RenderEngine() {};

	void Init();
protected:
	GLsizei win_height = 800, win_width = 800;
private:
	float lastFrame = 0.0f;
	bool InitilizeWindow();
	bool MainRendering();
};

#endif