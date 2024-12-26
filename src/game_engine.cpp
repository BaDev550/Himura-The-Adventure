#include <game_engine.h>

SpriteRenderer* Renderer;

void GameEngine::Init()
{
    ResourceManager::LoadShader("resources/shaders/default.vs", "resources/shaders/default.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800),static_cast<float>(800), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("resources/textures/test.png", true, "himura");
    Renderer->initRenderData();
}

void GameEngine::Update(float dt)
{
}

void GameEngine::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("himura"),
        glm::vec2(200.0f, 200.0f), glm::vec2(150.0f, 150.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void GameEngine::ProcessInput(float dt)
{
}
