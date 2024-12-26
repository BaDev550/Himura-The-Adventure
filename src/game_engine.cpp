#include <game_engine.h>

SpriteRenderer* Renderer;
GameObject* Player;

std::vector<GameObject*> ObjectInLevel;

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

    Player = new GameObject(glm::vec2(0, 0), glm::vec2(150.0f, 150.0f), ResourceManager::GetTexture("char"), false);
    Player->rb.mass = 0.5f;

    AddObject(glm::vec2(0, 700), glm::vec2(800, 100), true, "container.jpg", true);

    Renderer->initRenderData();
}

void GameEngine::Update(float dt)
{
    this->DoCollisions();
    for (int i = 0; i < ObjectInLevel.size(); i++) { 
        ObjectInLevel[i]->rb.update(dt, ObjectInLevel[i]->Position);
        ObjectInLevel[i]->rb.applyForce(glm::vec2(0.0f, 10000.0f)*dt);
    }
    Player->rb.update(dt, Player->Position);
    Player->rb.applyForce(glm::vec2(0.0, 10000.0f)*dt);
}

void GameEngine::Render()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 800.0f));

    for (int i = 0; i < ObjectInLevel.size(); i++) { 
        ObjectInLevel[i]->Draw(*Renderer);
    }
    Player->Draw(*Renderer);
}

void GameEngine::ProcessInput(float dt, GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float velocity = 500 * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (Player->Position.x >= 0.0f) {
            Player->rb.applyForce(glm::vec2(-10.0f * 10000, 0)* dt);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (Player->Position.x <= 800.0f - Player->Size.x) {
            Player->rb.applyForce(glm::vec2(10.0f * 10000, 0)* dt);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (Player->Position.x <= 800.0f - Player->Size.x) {
            Player->rb.applyForce(glm::vec2(0, -1.0f * 100000) * dt);
        }
    }
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    //    if (Player->Position.y >= 0.0f) {
    //        Player->rb.applyForce(glm::vec2(0.0, -10.0f * 10000)* dt);
    //    }
    //}
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    //    if (Player->Position.y <= 800.0f - Player->Size.y) {
    //        Player->rb.applyForce(glm::vec2(0.0, 10.0f * 10000)* dt);
    //    }
    //}
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        Player = new GameObject(Player->Position, Player->Size, ResourceManager::GetTexture("face"), false);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        Player = new GameObject(Player->Position, Player->Size, ResourceManager::GetTexture("char"), false);
    }
}

void GameEngine::DoCollisions()
{
    for (GameObject* box : ObjectInLevel)
    {
        if (!box->Destroyed && box->HasCollision)
        {
            if (box->CheckCollision(*Player, *box)) {
                glm::vec2 overlapVector = box->Position - Player->Position;

                box->handleCollision(overlapVector, Player->Position, 1.0f);
                Player->rb.velocity = glm::vec2(0.0f, 0.0f);

                box->Color = glm::vec3(0.5f, 1.0f, 1.0f);
            }
            else {
                box->Color = glm::vec3(1.0f, 1.0f, 1.0f);
            }
        }
    }
}

void GameEngine::AddObject(glm::vec2 pos, glm::vec2 size, bool hasCollision, std::string sprite, bool IsStatic, float mass)
{
    GameObject* tmp_gobj;
    ResourceManager::LoadTexture(("resources/textures/" + sprite).c_str(), false, sprite);
    tmp_gobj = new GameObject(pos, size, ResourceManager::GetTexture(sprite), hasCollision);
    tmp_gobj->rb.isStatic=IsStatic;
    tmp_gobj->rb.mass=mass;

    if (tmp_gobj != nullptr) {
        ObjectInLevel.push_back(tmp_gobj);
    }
    else {
        std::cerr << "Failed to create GameObject!" << std::endl;
        return;
    }
}
