#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Events/KeyPressEvent.h>
#include <Components/WindowInfoSingletonComponent.h>

using namespace ECS;

// �������ĸ���������
class KeyPressingSystem : public EntitySystem {
public:

	// ÿ����ѯ��ʱ����� GUI û������ʾ���ͼ�⵱ǰ���µİ�ť������ emit ����Ӧ��ť���¼�
	virtual void tick(class World* world, float deltaTime) override {
		world->each<WindowInfoSingletonComponent>([&](Entity* ent, ComponentHandle<WindowInfoSingletonComponent> c) -> void {
			if (c->showGUI) {
				return;
			}
			if (glfwGetKey(c->Window, GLFW_KEY_W) == GLFW_PRESS)
				world->emit<KeyPressEvent>({ W, deltaTime });
			if (glfwGetKey(c->Window, GLFW_KEY_S) == GLFW_PRESS)
				world->emit<KeyPressEvent>({ S, deltaTime });
			if (glfwGetKey(c->Window, GLFW_KEY_A) == GLFW_PRESS)
				world->emit<KeyPressEvent>({ A, deltaTime });
			if (glfwGetKey(c->Window, GLFW_KEY_D) == GLFW_PRESS)
				world->emit<KeyPressEvent>({ D, deltaTime });
			if (glfwGetKey(c->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				world->emit<KeyPressEvent>({ ESC, deltaTime });
		});
	}
};