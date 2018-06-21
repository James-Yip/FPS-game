#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Events/KeyEvents.h>
#include <Components/WindowInfoSingletonComponent.h>

using namespace ECS;

// �������ĸ���������
class KeyPressingSystem : public EntitySystem {
public:

	// ÿ����ѯ��ʱ����� GUI û������ʾ���ͼ�⵱ǰ���µİ�ť������ emit ����Ӧ��ť���¼�
	virtual void tick(class World* world, float deltaTime) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();

		if (windowCHandle->showGUI) {
			return;
		}
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_W) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ W, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_S) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ S, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_A) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ A, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_D) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ D, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ ESC, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ LEFT_SHIFT, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_SPACE) == GLFW_PRESS)
			world->emit<KeyPressEvent>({ SPACE, deltaTime });
		if (glfwGetMouseButton(windowCHandle->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			world->emit<MousePressEvent>({ MOUSE_LEFT, deltaTime });

		/*if (glfwGetKey(windowCHandle->Window, GLFW_KEY_W) == GLFW_REPEAT)
			world->emit<KeyRepeatEvent>({ W, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_S) == GLFW_REPEAT)
			world->emit<KeyRepeatEvent>({ S, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_A) == GLFW_REPEAT)
			world->emit<KeyRepeatEvent>({ A, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_D) == GLFW_REPEAT)
			world->emit<KeyRepeatEvent>({ D, deltaTime });*/

		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_W) == GLFW_RELEASE)
			world->emit<KeyReleaseEvent>({ W, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_S) == GLFW_RELEASE)
			world->emit<KeyReleaseEvent>({ S, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_A) == GLFW_RELEASE)
			world->emit<KeyReleaseEvent>({ A, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_D) == GLFW_RELEASE)
			world->emit<KeyReleaseEvent>({ D, deltaTime });
		if (glfwGetKey(windowCHandle->Window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
			world->emit<KeyReleaseEvent>({ LEFT_SHIFT, deltaTime });
	}
};