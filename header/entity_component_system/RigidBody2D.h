#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include <glm/glm.hpp>

class RigidBody2DComponent {
public:
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;
    bool isStatic;

    RigidBody2DComponent(float mass = 1.0f, bool isStatic = false)
        : velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), mass(mass), isStatic(isStatic) {}

    void applyForce(const glm::vec2& force) {
        if (!isStatic) {
            glm::vec2 resultingAcceleration = force / mass;
            acceleration += resultingAcceleration;
        }
    }

    void update(float deltaTime, glm::vec2& position) {
        if (!isStatic) {
            velocity += acceleration * deltaTime;
            position += velocity * deltaTime;
            acceleration = glm::vec2(0.0f, 0.0f);
        }
    }
};

#endif // RIGIDBODY_COMPONENT_H
