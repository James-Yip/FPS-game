#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Events/MouseMovementEvent.h>
#include <Components/WindowInfoSingletonComponent.h>

using namespace ECS;

// ��������ƶ��ı� camera �ӽ�
class MouseMovingSystem : public EntitySystem {
public:

	bool firstMouse;
	float lastX, lastY;

	MouseMovingSystem() {
		init();
	}

	void init() {
		firstMouse = true;
	}

	// ÿ����ѯ��ʱ����õ�ǰ����λ�ã������ offset���� emit ������ƶ����¼�
	virtual void tick(class World* world, float deltaTime) override {
		double xpos, ypos;

		world->each<WindowInfoSingletonComponent>([&](Entity* ent, ComponentHandle<WindowInfoSingletonComponent> c) -> void {
			int window_width, window_height;
			glfwGetWindowSize(c->Window, &window_width, &window_height);
			glfwGetCursorPos(c->Window, &xpos, &ypos);

			if (firstMouse) {
				lastX =(float)window_width / 2.0f;
				lastY = (float)window_height / 2.0f;
			}
		});
		
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		world->emit<MouseMovementEvent>({ xoffset ,yoffset });
	}
};