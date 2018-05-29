#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Components/MovementComponent.h>
#include <Components/PlayerComponent.h>
#include <Components/ObjectComponent.h>
#include <Components/WindowInfoSingletonComponent.h>
#include <Components/LightingInfoSingletonComponent.h>
#include <Events/KeyEvents.h>

using namespace ECS;

// ���ݼ�������������ߡ����Ȳ���
class PlayerActionSystem : public EntitySystem,
	public EventSubscriber<KeyPressEvent>,
	public EventSubscriber<KeyReleaseEvent> {
public:

	float speed_multiples;
	bool forward, backward, left, right, speed_up;

	virtual void configure(class World* world) override
	{
		world->subscribe<KeyPressEvent>(this);
		world->subscribe<KeyReleaseEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	virtual void receive(class World* world, const KeyPressEvent& event) override
	{	
		if (event.key == LEFT_SHIFT)
			this->speed_up = true;

		if (event.key == W)
			this->forward = true;
		if (event.key == S)
			this->backward = true;
		if (event.key == A)
			this->left = true;
		if (event.key == D)
			this->right = true;
	}

	virtual void receive(class World* world, const KeyReleaseEvent& event) override
	{
		if (event.key == LEFT_SHIFT)
			this->speed_up = false;

		if (event.key == W)
			this->forward = false;
		if (event.key == S)
			this->backward = false;
		if (event.key == A)
			this->left = false;
		if (event.key == D)
			this->right = false;
	}

	void init() {

	}

	// ���ݵ�ǰ�İ�������������ǰ	�ٶ�
	virtual void tick(class World* world, float deltaTime) override {
		world->each<PlayerComponent>([&](Entity* ent, ComponentHandle<PlayerComponent> playerCHandle) -> void {
			ComponentHandle<MovementComponent> movementCHandle = ent->get<MovementComponent>();
			ComponentHandle<PositionComponent> positionCHandle = ent->get<PositionComponent>();
			glm::vec3 unit_front = glm::normalize(glm::vec3(positionCHandle->Front.x, 0.0f, positionCHandle->Front.z)) * 10.0f;
			glm::vec3 unit_right = glm::normalize(glm::vec3(positionCHandle->Right.x, 0.0f, positionCHandle->Right.z)) * 10.0f;

			movementCHandle->Velocity = (float)forward * unit_front - (float)backward * unit_front + (float)right * unit_right - (float)left * unit_right;
			movementCHandle->Velocity += movementCHandle->Velocity * (float)speed_up * 3.0f;
		});
	}
};