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

	// ÿ����ѯ��ʱ����� GUI û������ʾ���ͻ�õ�ǰ����λ�ã������ offset���� emit ������ƶ����¼�
	virtual void tick(class World* world, float deltaTime) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();
		
		if (windowCHandle->showGUI) {
			firstMouse = true;
			return;
		}

		double xpos, ypos;
		int window_width, window_height;
		glfwGetWindowSize(windowCHandle->Window, &window_width, &window_height);
		glfwGetCursorPos(windowCHandle->Window, &xpos, &ypos);

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