#ifndef SPRITE_RENDERER_CLASS_H
#define SPRITE_RENDERER_CLASS_H
#pragma once

#include <render_engine/Shader.h>
#include <render_engine/Texture.h>

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);

    void DrawSprite(const Texture2D& texture, glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));
private:
    Shader       shader;
    unsigned int quadVAO;

    void initRenderData();
};

#endif 