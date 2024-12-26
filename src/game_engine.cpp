#include <game_engine.h>

SpriteRenderer* Renderer;
GameObject* Player;

void GameEngine::Init()
{
    ResourceManager::LoadShader("resources/shaders/default.vs", "resources/shaders/default.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800),static_cast<float>(800), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);

    ResourceManager::LoadTexture("resources/textures/background.png", false, "background");
    ResourceManager::LoadTexture("resources/textures/test.png", true, "char");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "face");

    Player = new GameObject(glm::vec2(0, 0), glm::vec2(150.0f, 150.0f), ResourceManager::GetTexture("char"));
    ObjectInLevel.push_back(GameObject(glm::vec2(150, 300), glm::vec2(150.0f, 150.0f), ResourceManager::GetTexture("face")));

    Renderer->initRenderData();
}

void GameEngine::Update(float dt)
{
    this->DoCollisions();
}

void GameEngine::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 800.0f));

    Player->Draw(*Renderer);
    for (GameObject& box : ObjectInLevel) { box.Draw(*Renderer); }
}

void GameEngine::ProcessInput(float dt, GLFWwindow* window)
{
    float velocity = 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (Player->Position.x >= 0.0f) {
            Player->Position.x -= velocity;
            std::cout << "Characters new pos in x: " << Player->Position.x << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (Player->Position.x <= 800.0f - Player->Size.x) {
            Player->Position.x += velocity;
            std::cout << "Characters new pos in x: " << Player->Position.x << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (Player->Position.y >= 0.0f) {
            Player->Position.y -= velocity;
            std::cout << "Characters new pos in y: " << Player->Position.y << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (Player->Position.y <= 800.0f - Player->Size.y) {
            Player->Position.y += velocity;
            std::cout << "Characters new pos in y: "<< Player->Position.y << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        Player = new GameObject(Player->Position, Player->Size, ResourceManager::GetTexture("face"));
        std::cout << "Character texture changed" << std::endl;
    }
}

bool CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    return collisionX && collisionY;
}

void GameEngine::DoCollisions()
{
    for (GameObject& box : ObjectInLevel)
    {
        if (!box.Destroyed)
        {
            if (CheckCollision(*Player, box))
            {
                if (!box.IsSolid) {
                    std::cout << "Colided" << std::endl;
                }
            }
        }
    }
}