#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Components/PositionComponent.h>
#include <Components/MovementComponent.h>
#include <Components/ObjectComponent.h>

using namespace ECS;

// ����Movement���ݣ�����entity��Position����
class MovementSystem : public EntitySystem {
public:

    MovementSystem() {}

    void updateVertices(vector<Vertex> &vertices, glm::vec3 shift) {
        for (int i = 0; i < vertices.size(); ++i) {
            vertices[i].Position += shift;
        }
    }

    // ÿ����ѯ��ʱ��Ϊÿһ�������MovementComponent��entity����λ�����ݣ�������Position����
    virtual void tick(class World* world, float deltaTime) override {
        world->each<MovementComponent, ObjectComponent>(
        [&](Entity* ent,  
            ComponentHandle<MovementComponent> movementCHandle,
            ComponentHandle<ObjectComponent> objectCHandle) -> void {
            glm::vec3 v = movementCHandle->Velocity;
            glm::vec3 a = movementCHandle->Acceleration;
            glm::vec3 shift = v * deltaTime;
            movementCHandle->Velocity = v + a * deltaTime;
            //printf("(%f, %f, %f)\n", shift.x, shift.y, shift.z);
            movementCHandle->Print();
            // ����vertices��ÿһ��Vertex��Position���ݲ����͵�GPU����
            for (int i = 0; i < objectCHandle->meshes[0].vertices.size(); ++i) {
                objectCHandle->meshes[0].vertices[i].Position += shift;
            }
            objectCHandle->meshes[0].updateVerticesInGPU();
        });
    }
};