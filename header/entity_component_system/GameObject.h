#ifndef GAMEOBJECT_CLASS_HEADER
#define GAMEOBJECT_CLASS_HEADER
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <render_engine/Texture.h>
#include <entity_component_system/sprite_renderer.h>
#include <entity_component_system/RigidBody2D.h>

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};


class GameObject
{
public:
	GameObject();
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool HasCollision;
	bool Destroyed;
	RigidBody2DComponent rb;

	Texture2D Sprite;
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, bool hasCollision, glm::vec3 color = glm::vec3(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer& renderer);

	Direction VectorDirection(glm::vec2 target);
	bool CheckCollision(GameObject& one, GameObject& two);
	void handleCollision(glm::vec2 overlapVector, glm::vec2& playerPosition, float blockDistance);
};

#endif // !GAMEOBJECT_CLASS_HEADER