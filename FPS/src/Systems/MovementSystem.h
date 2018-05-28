#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Components/PositionComponent.h>
#include <Components/MovementComponent.h>

using namespace ECS;

// ����Movement���ݣ�����entity��Position����
class MovementSystem : public EntitySystem {
public:

    MovementSystem() {}

    // ÿ����ѯ��ʱ��Ϊÿһ�������MovementComponent��entity����λ�����ݣ�������Position����
    virtual void tick(class World* world, float deltaTime) override {
        world->each<MovementComponent, PositionComponent>(
        [&](Entity* ent,
            ComponentHandle<MovementComponent> movementCHandle,
            ComponentHandle<PositionComponent> positionCHandle) -> void {
            glm::vec3 v = movementCHandle->Velocity;
            glm::vec3 a = movementCHandle->Acceleration;
            glm::vec3 shift = v * deltaTime;
            movementCHandle->Velocity = v + a * deltaTime;
            positionCHandle->Position += shift;
        });
    }
};