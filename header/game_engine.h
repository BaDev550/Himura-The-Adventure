#ifndef GAME_ENGINE_HEADER_CLASS
#define GAME_ENGINE_HEADER_CLASS
#pragma once

#include <ResourceManager.h>
#include <entity_component_system/sprite_renderer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CurrentGameState
{
	CGS_IN,
	CGS_LOST,
	CGS_WIN
};

class GameEngine
{
public:
	GameEngine() {};
	CurrentGameState State;

	void Init();
	void Update(float dt);
	void Render();
	void ProcessInput(float dt);
};

#endif