#pragma once
#include <GLFW/glfw3.h>

#include "Camera.h"
#include <ECS.h>
#include <Components/MeshComponent.h>
#include <Components/CameraInfoSingletonComponent.h>
#include <Components/WindowInfoSingletonComponent.h>
#include <Components/LightingInfoSingletonComponent.h>
#include <Events/MouseMovementEvent.h>
#include <Events/KeyPressEvent.h>

using namespace ECS;

// ���� camera ��λ�ú����ǵ���Ϣ����������� pos �� viewmatrix �� component ��Ϣ
class CameraMovingSystem : public EntitySystem, 
	public EventSubscriber<MouseMovementEvent>,
	public EventSubscriber<KeyPressEvent> {
public:

	Camera camera;

	virtual void configure(class World* world) override
	{
		// �ǵ�ע����Ҫ���ܵ��¼���
		world->subscribe<MouseMovementEvent>(this);
		world->subscribe<KeyPressEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	// ���յ�����ƶ����¼��󣬸�������λ��
	virtual void receive(class World* world, const MouseMovementEvent& event) override
	{
		camera.ProcessMouseMovement(event.xoffset, event.yoffset);
	}

	// ���յ� WASD ���µ��¼��󣬸��� Camera ��λ��
	virtual void receive(class World* world, const KeyPressEvent& event) override
	{
		if (event.key == W)
			camera.ProcessKeyboard(FORWARD, event.deltaTime);
		if (event.key == S)
			camera.ProcessKeyboard(BACKWARD, event.deltaTime);
		if (event.key == A)
			camera.ProcessKeyboard(LEFT, event.deltaTime);
		if (event.key == D)
			camera.ProcessKeyboard(RIGHT, event.deltaTime);
	}

	CameraMovingSystem(glm::vec3 _cameraPosition) {
		camera.Position = _cameraPosition;
	}

	void init() {
		
	}

	// ÿ����ѯ��ʱ���Ͱ����µ� camera λ�ú��ӽǸ���
	virtual void tick(class World* world, float deltaTime) override {
		ComponentHandle<CameraInfoSingletonComponent> cameraCHandle = world->getSingletonComponent<CameraInfoSingletonComponent>();

		cameraCHandle->CameraViewMatrix = camera.GetViewMatrix();
		cameraCHandle->CameraPos = camera.Position;
	}
};