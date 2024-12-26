#ifndef GAMEOBJECT_CLASS_HEADER
#define GAMEOBJECT_CLASS_HEADER
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <render_engine/Texture.h>
#include <entity_component_system/sprite_renderer.h>

class GameObject
{
public:
	GameObject();
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool Destroyed;

	Texture2D Sprite;
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer& renderer);
};

#endif // !GAMEOBJECT_CLASS_HEADER