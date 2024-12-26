#include "entity_component_system/GameObject.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, bool hasCollision, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), HasCollision(hasCollision), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
    if (HasCollision) { renderer.DrawCollision(this->Position, this->Size, this->Color); };
}

Direction GameObject::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  
        glm::vec2(1.0f, 0.0f),  
        glm::vec2(0.0f, -1.0f), 
        glm::vec2(-1.0f, 0.0f)  
    };

    float max = -1.0f;
    int best_match = -1;

    for (int i = 0; i < 4; i++) {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }

    return (Direction)best_match;
}

bool GameObject::CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    return collisionX && collisionY;
}

void GameObject::handleCollision(glm::vec2 overlapVector, glm::vec2& playerPosition, float blockDistance) {
    Direction collisionDirection = VectorDirection(overlapVector);
    glm::vec2 absOverlap = glm::abs(overlapVector);
    if (absOverlap.x > absOverlap.y) {
        if (overlapVector.y > 0) {
            playerPosition.y -= blockDistance;
        }
        else {
            playerPosition.y += blockDistance;
        }
    }
    else {
        if (overlapVector.x > 0) {
            playerPosition.x -= blockDistance;
        }
        else {
            playerPosition.x += blockDistance;
        }
    }
}