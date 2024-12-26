#ifndef GAME_ENGINE_HEADER_CLASS
#define GAME_ENGINE_HEADER_CLASS
#pragma once

#include <vector>

#include <ResourceManager.h>
#include <entity_component_system/sprite_renderer.h>
#include <entity_component_system/GameObject.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

enum CurrentGameState
{
	CGS_IN,
	CGS_LOST,
	CGS_WIN
};

class GameEngine
{
protected:
	GLsizei Width = 800, Height = 800;
	CurrentGameState State = CGS_IN;
public:
	GameEngine() {
	};

	void Init();
	void Update(float dt);
	void Render();
	void ProcessInput(float dt, GLFWwindow* window);

	void DoCollisions();

	void AddObject(glm::vec2 pos, glm::vec2 size, bool hasCollision, std::string sprite, bool IsStatic = false, float mass = 1.0f);
};

#endif